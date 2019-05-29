#include <array>
#include <iostream>
#include <sstream>

#include <pprint/pprint.hpp>


int main()
{
    std::stringstream stream;
    pprint::PrettyPrinter printer(stream);

    printer.print(5);
    printer.print(3.14f);
    printer.print(2.718);
    printer.print(true);
    printer.print('x');
    printer.print("Hello, 世界");
    printer.print(nullptr);

    typedef std::array<std::array<int, 3>, 3> Mat3x3;
    Mat3x3 matrix;
    matrix[0] = {1, 2, 3};
    matrix[1] = {4, 5, 6};
    matrix[2] = {7, 8, 9};
    printer.print("Matrix =", matrix);

    std::cout << stream.str() << std::endl;

    return 0;
}
