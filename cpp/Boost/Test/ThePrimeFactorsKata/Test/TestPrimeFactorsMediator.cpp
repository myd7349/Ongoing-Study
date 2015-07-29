// 2015-07-29T09:29+08:00
#include <boost/test/unit_test.hpp>

#include "PrimeFactorsMediator.h"

class FakePrimeFactorsDialog : public IPrimeFactorsDialog
{
public:
    FakePrimeFactorsDialog() : EnableOKButtonCalled(false), EnableOKButtonLastEnabled(false) {}
    virtual ~FakePrimeFactorsDialog() {}

    bool EnableOKButtonCalled;
    bool EnableOKButtonLastEnabled;

    virtual void EnableOKButton(bool enabled) 
    {
        EnableOKButtonCalled = true;
        EnableOKButtonLastEnabled = enabled;
    }

    bool ValueTextCalled;
    std::string ValueTextFakeResult;

    virtual std::string ValueText()
    {
        ValueTextCalled = true;
        return ValueTextFakeResult;
    }

    void AssertOKButtonEnabled(bool enabled)
    {
        BOOST_REQUIRE(EnableOKButtonCalled);
        BOOST_REQUIRE_EQUAL(enabled, EnableOKButtonLastEnabled);
    }
};

struct TestPrimeFactorsMediator
{
    TestPrimeFactorsMediator() : m_dialog(), m_mediator(&m_dialog) {}

    FakePrimeFactorsDialog m_dialog;
    PrimeFactorsMediator m_mediator;
};

BOOST_AUTO_TEST_SUITE(PrimeFactorsMediatorSuite)

BOOST_FIXTURE_TEST_CASE(OKButtonInitiallyDisabled, TestPrimeFactorsMediator)
{
    m_dialog.AssertOKButtonEnabled(false);
}

BOOST_FIXTURE_TEST_CASE(OKButtonEnabledWithValidInteger, TestPrimeFactorsMediator)
{
    m_dialog.ValueTextFakeResult = "123";
    m_mediator.ValueTextChanged();
    BOOST_REQUIRE(m_dialog.ValueTextCalled);
    m_dialog.AssertOKButtonEnabled(true);
}

BOOST_FIXTURE_TEST_CASE(OKButtonDisabledWithEmptyText, TestPrimeFactorsMediator)
{
    m_mediator.ValueTextChanged();
    BOOST_REQUIRE(m_dialog.ValueTextCalled);
    m_dialog.AssertOKButtonEnabled(false);
}

BOOST_FIXTURE_TEST_CASE(OKDisabledWithInvalidIntegerText, TestPrimeFactorsMediator)
{
    m_dialog.ValueTextFakeResult = "Invalid";
    m_mediator.ValueTextChanged();
    BOOST_REQUIRE(m_dialog.ValueTextCalled);
    m_dialog.AssertOKButtonEnabled(false);
}

BOOST_AUTO_TEST_SUITE_END()

// References:
// [C++ Unit Tests With Boost.Test, Part 4](https://legalizeadulthood.wordpress.com/2009/07/05/c-unit-tests-with-boost-test-part-4/)
// [C++ Unit Tests With Boost.Test, Part 5](https://legalizeadulthood.wordpress.com/2009/07/05/c-unit-tests-with-boost-test-part-5/)
