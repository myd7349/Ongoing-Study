// 2015-07-29T09:23+08:00
#ifndef PRIME_FACTORS_MEDIATOR_H_
#define PRIME_FACTORS_MEDIATOR_H_

#include <string>

class IPrimeFactorsDialog
{
public:
    virtual ~IPrimeFactorsDialog() {}
    virtual void EnableOKButton(bool enabled) = 0;
    virtual std::string ValueText() = 0;
};

class PrimeFactorsMediator
{
public:
    PrimeFactorsMediator(IPrimeFactorsDialog *dialog);
    ~PrimeFactorsMediator();

    void ValueTextChanged();

private:
    IPrimeFactorsDialog *m_dialog;
};

#endif // PRIME_FACTORS_MEDIATOR_H_

// References:
// [C++ Unit Tests With Boost.Test, Part 4](https://legalizeadulthood.wordpress.com/2009/07/05/c-unit-tests-with-boost-test-part-4/)
