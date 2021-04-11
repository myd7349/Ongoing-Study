// clang-format off
#include "pch.h"
#include "Person.h"

#include "../../MarshalCppClassV1/NativeClassLib/Person.h"

using namespace System::Runtime::InteropServices;

namespace NativeClassLibCLRBridge
{
    Person::Person(String^ name, int age)
    {
        person_ = new ::Person(msclr::interop::marshal_as<std::string>(name).c_str(), age);
    }


    Person::~Person()
    {
        delete person_;
    }


    String^ Person::GetName()
    {
        return msclr::interop::marshal_as<String^>(person_->GetName());
    }


    void Person::SetName(String^ name)
    {
        person_->SetName(msclr::interop::marshal_as<std::string>(name).c_str());
    }


    int Person::GetAge()
    {
        return person_->GetAge();
    }


    void Person::SetAge(int age)
    {
        person_->SetAge(age);
    }


    void Person::Say(String^ what)
    {
        person_->Say(msclr::interop::marshal_as<std::string>(what).c_str());
    }
}


// References:
// [How to Marshal a C++ Class](https://www.codeproject.com/Articles/18032/How-to-Marshal-a-C-Class)
// [Need to convert String^ to char *](https://stackoverflow.com/questions/2178023/need-to-convert-string-to-char)
// [C++/CLI Converting from System::String^ to std::string](https://stackoverflow.com/questions/946813/c-cli-converting-from-systemstring-to-stdstring)
// clang-format on
