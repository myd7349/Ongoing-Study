#include <iostream>

#include <Eigen/Dense>


int main()
{
    // Size set at run time:
    {
        Eigen::MatrixXd m = Eigen::MatrixXd::Random(3, 3);
        m = (m + Eigen::MatrixXd::Constant(3, 3, 1.2)) * 50;
        std::cout << "m =" << std::endl << m << std::endl;
        Eigen::VectorXd v(3);
        v << 1, 2, 3;
        std::cout << "m * v =" << std::endl << m * v << std::endl;
    }

    // Size set at compile time:
    {
        Eigen::Matrix3d m = Eigen::Matrix3d::Random();
        m = (m + Eigen::Matrix3d::Constant(1.2)) * 50;
        std::cout << "m =" << std::endl << m << std::endl;
        
        Eigen::Vector3d v(1, 2, 3);
        std::cout << "m * v =" << std::endl << m * v << std::endl;
    }

    return 0;
}


// References:
// https://eigen.tuxfamily.org/dox/GettingStarted.html
