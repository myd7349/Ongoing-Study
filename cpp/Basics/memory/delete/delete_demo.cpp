#include <iostream>


class A
{
public:
    A(int id) : id_(id) {}

    ~A()
    {
        std::cout << "~A" << id_ << std::endl;
    }

private:
    int id_;
};


int main()
{
    {
        A *a1 = new A(1);
        A *a2 = new A(2);
        delete a1, a2;
    }

    {
        A *a1 = new A(1);
        A *a2 = new A(2);
        delete (a1, a2);
    }

    return 0;
}
