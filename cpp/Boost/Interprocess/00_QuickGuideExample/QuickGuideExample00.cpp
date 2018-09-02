#include <cstdlib>
#include <sstream>

#include <boost/interprocess/managed_shared_memory.hpp>


int main(int argc, char *argv[])
{
    namespace bipc = boost::interprocess;

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

        bipc::managed_shared_memory::size_type free_memory = segment.get_free_memory();
        void *ptr = segment.allocate(1024);

        if (free_memory <= segment.get_free_memory())
            return EXIT_FAILURE;

        bipc::managed_shared_memory::handle_t handle = segment.get_handle_from_address(ptr);

        std::stringstream ss;
        ss << argv[0] << " " << handle << std::ends;

        // Create child process
        if (0 != std::system(ss.str().c_str()))
            return EXIT_FAILURE;

        if (free_memory != segment.get_free_memory())
            return EXIT_FAILURE;
    }
    else
    {
        bipc::managed_shared_memory segment(bipc::open_only, name);

        bipc::managed_shared_memory::handle_t handle = 0;

        std::stringstream ss;
        ss << argv[1];
        ss >> handle;

        void *msg = segment.get_address_from_handle(handle);

        segment.deallocate(msg);
    }

    return 0;
}

// References:
// https://www.boost.org/doc/libs/1_65_0/doc/html/interprocess/quick_guide.html#interprocess.quick_guide.qg_memory_pool
