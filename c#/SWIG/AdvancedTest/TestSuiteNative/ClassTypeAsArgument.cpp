#include "ClassTypeAsArgument.h"
#include "Win32Common.h"

void Person::Say(const std::wstring &what) const
{
    MessageBoxW(NULL, what.c_str(), L"Hello!", MB_OK | MB_ICONINFORMATION);
}

void Person::Say(const Message &msg) const
{
    Say(msg.message);
}