// 2015-05-11T11:29+08:00
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

class Stupid {
public:
    Stupid(std::size_t length) {
        assert(length > 0);
        data_buffer_ = new double[length];
    }

    virtual ~Stupid() {
        std::cout << "Too young! Too naive!\n";
        delete[] data_buffer_;
    }
private:
    double *data_buffer_;
};

int main()
{
    const std::size_t Count = 4;

    std::vector<Stupid> vs(Count, 10);

    return 0;
}

// In VS2010, this program crashes!
