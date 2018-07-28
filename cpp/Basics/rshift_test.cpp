#include <cstdint>
#include <iostream>


int main()
{
    using std::uint32_t;
    using std::uint64_t;
    
    uint32_t file_size = 26728;

    // VS2010/VS2017:
    // warning C4293: '>>' : shift count negative or too big, undefined behavior
    // Code::Blocks 17.12(With gcc 5.1.0):
    // warning: right shift count >= width of type [-Wshift-count-overflow]
    //
    // Output:
    // VS2010/VS2017: 26728 0
    // Code::Blocks: 26728 0
    std::cout << (file_size >> 32) << " ";
    std::cout << ((uint64_t)file_size >> 32) << std::endl;

    return 0;
}


// References:
// https://github.com/carlomilanesi/cpp-mmf/pull/2
// https://stackoverflow.com/questions/3501878/force-gcc-to-compile-32-bit-programs-on-64-bit-platform
