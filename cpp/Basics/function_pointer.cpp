#include <functional>
#include <iostream>
#include <typeinfo>

void Foo() {
    std::cout << "Foo()\n";
}

void Foo(int x) {
    std::cout << "Foo(" << x << ")\n";
}


typedef void FooT(int);
typedef void (*FooPT)(int);


int main() {
    //FooT f1 = static_cast<FooT>(Foo);
    //FooT f2 = static_cast<FooT>(&Foo);
    FooPT f3 = static_cast<FooPT>(Foo);
    FooPT f4 = static_cast<FooPT>(&Foo);
    //std::function<FooT> f5 = static_cast<FooT>(&Foo);
    std::function<FooT> f6 = static_cast<FooT *>(&Foo);
    std::function<FooT> f7 = static_cast<FooPT>(&Foo);
    //std::function<FooPT> f8 = static_cast<FooPT>(&Foo);
    //std::function<FooPT> f9 = static_cast<FooPT>(Foo);
    //std::function<FooPT> f10(static_cast<FooPT>(&Foo));
    std::cout << typeid(FooT).name() << std::endl; // FviE
    std::cout << typeid(FooPT).name() << std::endl; // PFviE
    std::cout << (typeid(FooT) == typeid(FooPT)) << std::endl;
    return 0;
}
