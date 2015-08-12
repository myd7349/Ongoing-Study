// 2015-08-12T11:38+08:00
#include <iostream>

#include "../../common.h"

#ifndef USE_ARRAY_DELETER
# define USE_ARRAY_DELETER (1)
#endif

#ifndef USE_TR1
# define USE_TR1 (0)
#endif

#if USE_TR1
# if defined(__GNUC__) || defined(__GNUG__)
#  include <tr1/memory>
# else
#  include <memory>
# endif
namespace ST = std::tr1;
#else
# include <memory>
namespace ST = std;
#endif

struct Integer {
    Integer(int i = 0) : i_(i) {
        dump_(__func__);
    }

    ~Integer() {
        dump_(__func__);
    }

private:
    void dump_(const char *name) {
        std::cout << name << "(): " << i_ << std::endl;
    }

    int i_;
};

int main()
{    
    {
#if USE_ARRAY_DELETER
        ST::shared_ptr<Integer> arr(
# if !defined(_MSC_VER) || _MSC_VER > 1800
            // In VS2013, code below behaves strangely:
            // the destructor of `Integer` never been called. 
            new Integer[3] {0, 1, 2}
# else
            new Integer[3] //{0, 1, 2}
# endif
            ,
            std::default_delete<Integer[]>());
#else
        // Ouch!
        ST::shared_ptr<Integer> arr(new Integer[3] {0, 1, 2});
#endif
    }

    PAUSE();
    return 0;
}

// References:
// Effective C++ 3E: Item 13
// [shared_ptr to an array : should it be used?](http://stackoverflow.com/questions/13061979/shared-ptr-to-an-array-should-it-be-used)
// [Why isn't there a std::shared_ptr<T[]> specialisation?](http://stackoverflow.com/questions/8947579/why-isnt-there-a-stdshared-ptrt-specialisation)
// [TR1 not working with gcc and Cmake](http://stackoverflow.com/questions/10205292/tr1-not-working-with-gcc-and-cmake)
