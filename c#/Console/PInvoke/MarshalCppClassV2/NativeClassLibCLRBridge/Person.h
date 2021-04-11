// clang-format off
#pragma once

using namespace System;

class Person;

namespace NativeClassLibCLRBridge
{
	public ref class Person
	{
    public:
        Person(String^ name, int age);
        ~Person();

        property String^ Name
        {
            String^ get()
            {
                return GetName();
            }

            void set(String^ value)
            {
                SetName(value);
            }
        }

        property int Age
        {
            int get()
            {
                return GetAge();
            }

            void set(int value)
            {
                SetAge(value);
            }
        }

        void Say(String ^ what);

    private:
        String^ GetName();
        void SetName(String^ name);

        int GetAge();
        void SetAge(int age);

        ::Person *person_;
	};
}

// References:
// [What are properties in C++/CLI?](https://stackoverflow.com/questions/4912183/what-are-properties-in-c-cli)
// [How to: Use Properties in C++/CLI](https://docs.microsoft.com/en-us/cpp/dotnet/how-to-use-properties-in-cpp-cli?view=msvc-160)
// clang-format on
