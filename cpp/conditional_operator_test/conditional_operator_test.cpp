// 2016-01-13T09:42+08:00
#include <iostream>

const int LEAD_NUMBERS = 12;

typedef double *Buffer[LEAD_NUMBERS];

class Data
{
public:
    Data(bool cond) : cond_(cond) {}

    const Buffer &GetData() const {
#if 1
        // In VS2010, code below causes a syntax error:
        // error C2440: 'return' : cannot convert from 'double *const *' to 'const Buffer (&)'
        //     Reason: cannot convert from 'double *const *' to 'const Buffer'
        //     There are no conversions to array types, although there are conversions to references or pointers to arrays
        return cond_ ? buf0_ : buf1_;
#else
        if (cond_) {
            return buf0_;
        } else {
            return buf1_;
        }
#endif
    }

private:
    bool cond_;

    Buffer buf0_;
    Buffer buf1_;
};

int main()
{
    return 0;
}
