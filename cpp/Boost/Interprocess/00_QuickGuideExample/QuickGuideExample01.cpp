#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

#include <boost/interprocess/managed_shared_memory.hpp>


int main(int argc, char *argv[])
{
    namespace bipc = boost::interprocess;
    using MyPair = std::pair<double, int>;

    const char *name = "MySharedMemory";

    if (argc == 1)
    {
        struct SharedMemoryRemover
        {
            SharedMemoryRemover(const char *name)
                : name_(name)
            {
                bipc::shared_memory_object::remove(name_);
            }

            ~SharedMemoryRemover()
            {
                bipc::shared_memory_object::remove(name_);
            }

        private:
            const char *name_;
        } remover(name);

        bipc::managed_shared_memory segment(bipc::create_only, name, 65536);

        MyPair *instance = segment.construct<MyPair>
            ("MyPair instance")
            (0.0, 0);

        MyPair *array = segment.construct<MyPair>
            ("MyPair array")
            [10]
        (0.0, 0);

        float floats[] { 0.0, 1.0, 2.0 };
        int ints[] { 0, 1, 2 };

        MyPair *array_it = segment.construct_it<MyPair>
            ("MyPair array from it")
            [3]
        (&floats[0], &ints[0]);

        std::string s(argv[0]);
        s += " child";
        if (0 != std::system(s.c_str()))
            return EXIT_FAILURE;

        if (segment.find<MyPair>("MyPair array").first ||
            segment.find<MyPair>("MyPair instance").first ||
            segment.find<MyPair>("MyPair array from it").first)
            return EXIT_FAILURE;
    }
    else
    {
        bipc::managed_shared_memory segment(bipc::open_only, name);

        std::pair<MyPair *, bipc::managed_shared_memory::size_type> res;

        res = segment.find<MyPair>("MyPair array");
        assert(res.second == 10);
        std::cout << "MyPair array:\n";
        for (decltype(res.second) i = 0; i < res.second; ++i)
            std::cout << res.first[i].first << ": " << res.first[i].second << std::endl;
        segment.destroy<MyPair>("MyPair array");

        res = segment.find<MyPair>("MyPair instance");
        assert(res.second == 1);
        std::cout << "MyPair instance:\n";
        std::cout << res.first->first << ": " << res.first->second << std::endl;
        segment.destroy<MyPair>("MyPair instance");

        res = segment.find<MyPair>("MyPair array from it");
        assert(res.second == 3);
        std::cout << "MyPair array:\n";
        for (decltype(res.second) i = 0; i < res.second; ++i)
            std::cout << res.first[i].first << ": " << res.first[i].second << std::endl;
        segment.destroy<MyPair>("MyPair array from it");
    }

    return 0;
}

// References:
// https://www.boost.org/doc/libs/1_65_0/doc/html/interprocess/quick_guide.html#interprocess.quick_guide.qg_named_interprocess
