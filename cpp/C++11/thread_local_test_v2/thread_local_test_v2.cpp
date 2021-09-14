#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>


// In Win32, selecting and releasing the DC in different threads is not allowed.
class STAObject
{
public:
    STAObject(int property1, double property2)
        : thread_id_(std::this_thread::get_id())
        , property1_(property1)
        , property2_(property2)
    {
        std::cout << "#" << thread_id_  << " object " << static_cast<void *>(this) << " created." << std::endl;
    }

    ~STAObject()
    {
        std::cout << "#" << thread_id_  << " object " << static_cast<void *>(this) << " destroyed." << std::endl;

        if (std::this_thread::get_id() != thread_id_)
        {
            std::cout << "Bang! Object " << this << " is created on #" << thread_id_ << " but destroyed on #" << std::this_thread::get_id() << std::endl;
        }
    }

    int get_property_1() const { return property1_; }

    double get_property_2() const { return property2_; }

    std::thread::id owner() const { return thread_id_; }

    std::string to_string() const
    {
        std::ostringstream oss;
        oss << "STAObject(" << property1_ << "," << property2_ << ")@"
            << this;
        return oss.str();
    }

private:
    std::thread::id thread_id_;
    int property1_;
    double property2_;
};


class ContextV1
{
public:
    void set_property_1(int value)
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (!dirty_)
            dirty_ = property1_ != value;
        property1_ = value;
    }

    void set_property_2(double value)
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (!dirty_)
            dirty_ = property2_ != value;
        property2_ = value;
    }

    void visit()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (dirty_)
        {
            sta_ = std::make_unique<STAObject>(property1_, property2_);
            dirty_ = false;
        }
        
        std::cout << "#" << std::this_thread::get_id() << " " << sta_->to_string() << std::endl;
    }

private:
    std::mutex mutex_;

    std::unique_ptr<STAObject> sta_;
    bool dirty_{true};
    int property1_{0};
    double property2_{0};
};


void worker_v1(ContextV1 &context)
{
    int i = 0;

    while (i++ < 3)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        context.visit();
    }
}


#define USE_EMPLACE_BACK (1)
#define AT_MOST_ONE (1)

#if AT_MOST_ONE && USE_EMPLACE_BACK
# undef USE_EMPLACE_BACK
# define USE_EMPLACE_BACK (0)
#endif


class ContextV2
{
public:
    void set_property_1(int value)
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (!dirty_)
            dirty_ = property1_ != value;
        property1_ = value;
    }

    void set_property_2(double value)
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (!dirty_)
            dirty_ = property2_ != value;
        property2_ = value;
    }

    void visit()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (dirty_)
        {
            if (sta_ != nullptr && sta_->owner() != std::this_thread::get_id())
#if AT_MOST_ONE
                gc_memo_[sta_->owner()].reset(sta_.release());
#else
#if USE_EMPLACE_BACK
                // In VS2010, this won't work.
                gc_memo_[sta_->owner()].emplace_back(sta_.release());
                // Instead, you should:
                //auto owner = sta_->owner();
                //gc_memo_[owner].emplace_back(sta_.release());
#else
                gc_memo_[sta_->owner()].push_back(std::move(sta_));
#endif
#endif

            sta_ = std::make_unique<STAObject>(property1_, property2_);

            dirty_ = false;

#if AT_MOST_ONE
            gc_impl(false);
#endif
        }
        
        std::cout << "#" << std::this_thread::get_id() << " " << sta_->to_string() << std::endl;
    }

    void gc()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        gc_impl(true);
    }

private:
    void gc_impl(bool aggressive)
    {
        if (aggressive && sta_ != nullptr && sta_->owner() == std::this_thread::get_id())
        {
            sta_.reset();
            dirty_ = true;
        }

        auto pool_iterator = gc_memo_.find(std::this_thread::get_id());
        if (pool_iterator == gc_memo_.end())
            return;

        std::cout << "#" << std::this_thread::get_id() << " >>>>>> GC <<<<<<\n";

#if !AT_MOST_ONE
#ifndef NDEBUG
        auto &objects_to_be_gc = pool_iterator->second;
        for (auto &object : objects_to_be_gc)
        {
            std::cout << "#" << std::this_thread::get_id() << " > " << static_cast<const void *>(object.get()) << "\n";
            object.reset();
        }
#endif
#endif

        gc_memo_.erase(pool_iterator);
    }

    std::mutex mutex_;

    std::unique_ptr<STAObject> sta_;
    bool dirty_{true};
    int property1_{0};
    double property2_{0};

#if AT_MOST_ONE
    std::unordered_map<std::thread::id, std::unique_ptr<STAObject>> gc_memo_;
#else
#if USE_EMPLACE_BACK
    std::unordered_map<std::thread::id, std::list<std::shared_ptr<STAObject>>> gc_memo_;
#else
    std::unordered_map<std::thread::id, std::list<std::unique_ptr<STAObject>>> gc_memo_;
#endif
#endif
};


void worker_v2(ContextV2 &context)
{
    int i = 0;

    while (i++ < 3)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        context.visit();
    }

    context.gc();
}


class ContextV3
{
public:
    void set_property_1(int value)
    {
        std::lock_guard<std::mutex> guard(mutex_);
        property1_ = value;
    }

    void set_property_2(double value)
    {
        std::lock_guard<std::mutex> guard(mutex_);
        property2_ = value;
    }

    void visit()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        bool dirty = sta_ == nullptr || sta_->get_property_1() != property1_ || sta_->get_property_2() != property2_;
        if (dirty)
            sta_ = std::make_unique<STAObject>(property1_, property2_);
        
        std::cout << "#" << std::this_thread::get_id() << " " << sta_->to_string() << std::endl;
    }

private:
    static thread_local std::unique_ptr<STAObject> sta_;

    std::mutex mutex_;
    int property1_{0};
    double property2_{0};
};


thread_local std::unique_ptr<STAObject> ContextV3::sta_;


void worker_v3(ContextV3 &context)
{
    int i = 0;

    while (i++ < 3)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        context.visit();
    }
}


void context_v1_test()
{
    std::cout << "ContextV1 test:----------------------------------------------------------------" << std::endl;
    ContextV1 context;

    std::thread worker_thread(worker_v1, std::ref(context));

    for (int i = 0; i < 3; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        context.set_property_1(i);
        context.set_property_2(i * i);

        context.visit();
    }

    worker_thread.join();
}


void context_v2_test()
{
    std::cout << "ContextV2 test:----------------------------------------------------------------" << std::endl;
    ContextV2 context;

    std::thread worker_thread(worker_v2, std::ref(context));

    for (int i = 0; i < 3; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        context.set_property_1(i);
        context.set_property_2(i * i);

        context.visit();
    }

    worker_thread.join();

    context.gc();
}


void context_v3_test()
{
    std::cout << "ContextV3 test:----------------------------------------------------------------" << std::endl;
    ContextV3 context;

    std::thread worker_thread(worker_v3, std::ref(context));

    for (int i = 0; i < 3; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        context.set_property_1(i);
        context.set_property_2(i * i);

        context.visit();
    }

    worker_thread.join();
}


int main()
{
    std::cout << "Main thread: " << "#" << std::this_thread::get_id() << std::endl;

    context_v1_test();
    context_v2_test();
    context_v3_test();

    return 0;
}


// References:
// [How can I have non-static thread-local variable for each instance](https://stackoverflow.com/questions/41800919/how-can-i-have-non-static-thread-local-variable-for-each-instance)
// [What does [STAThread] do?](https://stackoverflow.com/questions/1361033/what-does-stathread-do)
// [What does Thread Affinity mean?](https://stackoverflow.com/questions/19587323/what-does-thread-affinity-mean)
// [Thread type for background drawing to a bitmap in MFC](https://stackoverflow.com/questions/2287114/thread-type-for-background-drawing-to-a-bitmap-in-mfc?rq=1)
// [Can you use thread local variables inside a class or structure](https://stackoverflow.com/questions/10999131/can-you-use-thread-local-variables-inside-a-class-or-structure)
