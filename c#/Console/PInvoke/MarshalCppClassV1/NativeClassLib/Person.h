#pragma once

#include <string>


#ifdef NATIVECLASSLIB_EXPORTS
#define NATIVECLASSLIB_API __declspec(dllexport)
#else
#define NATIVECLASSLIB_API __declspec(dllimport)
#endif

class Person {
 public:
  NATIVECLASSLIB_API Person(const char* name = "", int age = 0);
  NATIVECLASSLIB_API const char* GetName() const;
  NATIVECLASSLIB_API void SetName(const char* name);
  NATIVECLASSLIB_API int GetAge() const;
  NATIVECLASSLIB_API void SetAge(int age);
  NATIVECLASSLIB_API void Say(const char* what) const;

  NATIVECLASSLIB_API static Person* New(const char* name = "", int age = 0);
  NATIVECLASSLIB_API static void Delete(Person* person);
 private:
  std::string name_;
  int age_;
};

#ifdef __cplusplus
extern "C" {
#endif

NATIVECLASSLIB_API const char* GetArch();

#ifdef __cplusplus
}
#endif
