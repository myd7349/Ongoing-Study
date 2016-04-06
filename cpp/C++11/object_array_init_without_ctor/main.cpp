// 2016-04-06T16:11+08:00
#include <string>

#include "../../common.h"

class Integer {
public:
    Integer(int x) : x_(x) {}
    operator int() const { return x_; }

private:
    int x_;
};

int main()
{
    // 0.
    std::vector<Integer> ivec;
    for (int i = 0; i < 2; ++i)
        ivec.emplace_back(i);
    Println(ivec);

    // 1.
    const int SIZE = 2;
    int *integerArray = new int[SIZE]();
    for (int *p = integerArray; p < integerArray; ++p)
        std::cout << *p << std::endl;

    PAUSE();
    return 0;
}

// References:
// https://www.zhihu.com/question/41964713
// http://stackoverflow.com/questions/4754763/object-array-initialization-without-default-constructor
// http://stackoverflow.com/questions/2204176/how-to-initialise-memory-with-new-operator-in-c
// http://en.cppreference.com/w/cpp/container/vector/emplace_back
