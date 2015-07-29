// 2015-07-29T09:45+08:00
#include <sstream>

#include "PrimeFactorsMediator.h"

PrimeFactorsMediator::PrimeFactorsMediator(IPrimeFactorsDialog *dialog)
    : m_dialog(dialog)
{
    m_dialog->EnableOKButton(false);
}

PrimeFactorsMediator::~PrimeFactorsMediator()
{
}

void PrimeFactorsMediator::ValueTextChanged()
{
    std::istringstream stream(m_dialog->ValueText());
    int value;
    stream >> value;
    m_dialog->EnableOKButton(!stream.fail() && m_dialog->ValueText().length() > 0);
}
