#include <iostream>

#include <Eigen/Dense>


int main()
{
    Eigen::Matrix2d a;
    a << 1, 2,
         3, 4;
    Eigen::MatrixXd b(2, 2);
    b << 2, 3,
         1, 4;
    std::cout << "a + b =\n" << a + b << std::endl;
    std::cout << "a - b =\n" << a - b << std::endl;
    std::cout << "Doing a += b;" << std::endl;
    a += b;
    std::cout << "Now a =\n" << a << std::endl;
    Eigen::Vector3d v(1, 2, 3);
    Eigen::Vector3d w(1, 0, 0);
    std::cout << "-v + w - v =\n" << -v + w - v << std::endl;

    std::cout << "a^T =\n" << a.transpose() << std::endl;
    Eigen::MatrixXd c = a.transpose();
    std::cout << "c =\n" << c << std::endl;

    a = a.transpose(); // Do not do this!
    std::cout << "a =\n" << a << std::endl;

    a.transposeInPlace();
    std::cout << "a =\n" << a << std::endl;

    return 0;
}


// References:
// https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html
