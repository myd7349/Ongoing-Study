// 2017-04-26 17:45
#pragma once

#include <cassert>
#include <deque>

#include "Component.hpp"

class Composite : public Component
{
public:
    typedef std::deque<SharedComponentPtr> Children;

    // ??
    class CompositeElementIterator : Iterator<SharedComponentPtr>
    {
    public:
        CompositeElementIterator(Composite &composite)
            : composite_(composite), isDone_(true)
        {
        }
        
        virtual void First()
        {
            it_ = composite_.children_.begin();
            isDone_ = it_ == composite_.children_.end();
        }
        
        virtual void MoveNext()
        {
            if (!isDone_)
            {
                ++it_;
                isDone_ = it_ == composite_.children_.end();
            }
        }
        
        virtual bool IsDone()
        {
            return isDone_;
        }
        
        virtual SharedComponentPtr Current()
        {
            if (isDone_)
                throw StopIterationError();

            return *it_;
        }

    private:
        Composite &composite_;
        Children::iterator it_;
        bool isDone_;
    };

    class CompositeElementRecursiveBFSIterator : Iterator<SharedComponentPtr>
    {
    public:
        CompositeElementRecursiveBFSIterator(Composite &composite)
            : composite_(composite)
        {
        }
        
        virtual void First()
        {
            // clear the queue
            std::queue<SharedComponentPtr> emptyQueue;
            queue_.swap(emptyQueue);
            
            UpdateCurrentIterator(composite_);
        }
        
        virtual void MoveNext()
        {
            if (!current_->IsDone())
            {
                current_->MoveNext();
            }
            else if (!queue_.empty())
            {
                UpdateCurrentIterator(*queue_.front());
                queue_.pop();
            }
        }
        
        virtual bool IsDone()
        {
            return !current_ && current_->IsDone();
        }
        
        virtual SharedComponentPtr Current()
        {
            if (IsDone())
                throw StopIterationError();

            return current_->Current();
        }

    private:
        void UpdateCurrentIterator(Component &component)
        {
            assert(!current_ || current_->IsDone());
            
            current_ = component.CreateIterator();

            // the first shoot
            current_ = composite_.CreateIterator();
            for (current_->First(); !current_->IsDone(); current_->MoveNext())
                queue_.push(current_->Current());

            current_->First(); // reset iterator
        }

        Composite &composite_;
        std::queue<SharedComponentPtr> queue_;
        ComponentIterator current_;
    };

    class CompositeElementRecursiveDFSIterator : Iterator<SharedComponentPtr>
    {
    public:
        CompositeElementRecursiveDFSIterator(Composite &composite)
            : composite_(composite)
        {
        }
        
        virtual void First()
        {
        }
        
        virtual void MoveNext()
        {
        }
        
        virtual bool IsDone()
        {
        }
        
        virtual SharedComponentPtr Current()
        {
        }

    private:
        Composite &composite_;
    };

    virtual void Add(SharedComponentPtr child)
    {
        assert(child);

        if (!child)
            return;

        children_.push_back(child);
    }

    virtual void Remove(SharedComponentPtr child)
    {
        RemoveIf(child, [child](SharedComponentPtr e) { return e == child; });
    }

    virtual void RemoveIf(SharedComponentPtr child, std::function<bool(SharedComponentPtr)> pred)
    {
        assert(child);
        assert(pred);

        for (Children::iterator it = children_.begin(); it != children_.end(); )
        {
            if (pred(*it))
                children_.erase(it++);
            else
                ++it;
        }
    }

    virtual void Clear()
    {
        children_.clear();
    }

    virtual ComponentIterator CreateIterator(TraversalKind traversalKind = None)
    {
        switch (traversalKind)
        {
        case BFS:
            return std::make_shared<CompositeElementRecursiveBFSIterator>(this);
            break;
        case DFS:
            return std::make_shared<CompositeElementRecursiveDFSIterator>(this);
            break;
        default:
            break;
        }

        return std::make_shared<CompositeElementIterator>(this);
    }

private:
    Children children_;
};

// References:
// [Breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search)
// [How do I clear the std::queue efficiently?](http://stackoverflow.com/questions/709146/how-do-i-clear-the-stdqueue-efficiently)