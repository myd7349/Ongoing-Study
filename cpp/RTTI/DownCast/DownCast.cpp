// 2014-01-21T10:39+08:00
// 2015-03-05T08:31+08:00 Happy lantern festival!
#include <cassert> // assert
#include <cstddef> // std::size_t
#include <cstdlib> // EXIT_FAILURE
#include <iostream> // std::cerr
#include <new> // std::bad_alloc
#include <typeinfo> // RTTI, std::bad_cast, typeid

#include "../common.h"

class Useful {
public:
    virtual ~Useful() {}
    // Then 'Useful' is polymorphic.
    virtual void interfaceFromBase() {}
};

class MoreUseful : public Useful {
public:
    virtual ~MoreUseful() {}
    void interfaceInDerived() {}
};

int main()
{
    Useful *p[10] = {0};

    {
        std::size_t i = 0;
        try {
            for (; i < ARRAYSIZE(p); ++i) {
                if (i % 2 == 0) {
                    p[i] = new Useful;
                } else {
                    p[i] = new MoreUseful;
                }
            }
        } catch (std::bad_alloc &exp) {
            for (std::size_t j = 0; j < i; ++j) {
                delete p[j];
            }

            std::cerr << "std::bad_alloc thrown while allocating memory for p["
                << i << "]: " << exp.what() << "\n";
            return EXIT_FAILURE;
        }
    }

    for (std::size_t i = 0; i < ARRAYSIZE(p); ++i) {
        MoreUseful *pBase = NULL;
        try {
            // To do "dynamic cast", source type should be polymorphic.
            pBase = dynamic_cast<MoreUseful *>(p[i]);
            pBase->interfaceInDerived();
            // Do a bad dynamic cast on a pointer, then we will get a null pointer.
            if (NULL == pBase) {
                std::cerr << "Invalid downcast on p[" << i << "]: \""
                    << typeid(*p[i]).name() << "\" --> \"MoreUseful\"\n";
            }
        } catch (std::bad_cast &) {
            // never reached
            assert(false);
        }

        try {
            MoreUseful &refBase = dynamic_cast<MoreUseful &>(*p[i]);
            refBase.interfaceInDerived();
        } catch (std::bad_cast &exp) {
            // Do a bad dynamic cast on a reference,  an "std::bad_cast"
            // exception will be thrown.
            std::cerr << "Error occurs while attempting to downcast type \""
                << typeid(*p[i]).name() << "\" to type \"MoreUseful\": "
                << exp.what() << "\n";
        }
    }

    for (std::size_t i = 0; i < ARRAYSIZE(p); ++i) {
        delete p[i];
    }
    return 0;
}
