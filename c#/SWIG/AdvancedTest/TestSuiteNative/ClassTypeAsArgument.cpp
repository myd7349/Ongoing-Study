#include "ClassTypeAsArgument.h"

#define WIN32_LEAN_AND_MEAN
#define STRICT 1
#include <Windows.h>

void Person::Say(const std::wstring &what) const
{
    MessageBoxW(NULL, what.c_str(), L"Hello!", MB_OK | MB_ICONINFORMATION);
}

void Person::Say(const Message &msg) const
{
    Say(msg.message);
}