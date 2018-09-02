#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <utility>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>


namespace bipc = boost::interprocess;


struct list_node
{
    bipc::offset_ptr<list_node> next;
    int                         value;
};


int main(int argc, char *argv[])
{
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

        bipc::offset_ptr<list_node> prev = 0, current, first;

        for (int i = 0; i < 10; ++i, prev = current)
        {
            current = static_cast<list_node *>(segment.allocate(sizeof(list_node)));
            current->value = i;
            current->next = 0;

            if (!prev)
                first = current;
            else
                prev->next = current;
        }

        bipc::managed_shared_memory::handle_t handle = segment.get_handle_from_address(first.get());

        std::stringstream ss;
        ss << argv[0] << " " << handle << std::ends;
        if (0 != std::system(ss.str().c_str()))
            return EXIT_FAILURE;
    }
    else
    {
        bipc::managed_shared_memory segment(bipc::open_only, name);

        bipc::managed_shared_memory::handle_t handle;

        std::stringstream ss;
        ss << argv[1];
        ss >> handle;

        list_node *first = static_cast<list_node *>(segment.get_address_from_handle(handle));
        list_node *prev;

        while (first)
        {
            std::cout << first->value << std::endl;
            prev = first;
            first = first->next.get();
            segment.deallocate(prev);
        }
    }

    return 0;
}

// References:
// https://www.boost.org/doc/libs/1_65_0/doc/html/interprocess/quick_guide.html#interprocess.quick_guide.qg_offset_ptr
