// clang-format off
#include "pch.h"
#include "Person.h"

#include <cstdio>
// clang-format on

Person::Person(const char* name, int age) : name_(name), age_(age) {}

const char* Person::GetName() const { return name_.c_str(); }
void Person::SetName(const char* name) { name_ = name; }

int Person::GetAge() const { return age_; }
void Person::SetAge(int age) { age_ = age; }

void Person::Say(const char* what) const {
  std::printf("%s: %s\n", name_.c_str(), what);
}

Person* Person::New(const char* name, int age) { return new Person(name, age); }
void Person::Delete(Person* person) { delete person; }

const char* GetArch() {
#if defined(_WIN64)
  return "x64";
#elif defined(_WIN32)
  return "x86";
#else
  return "Unknown";
#endif
}
