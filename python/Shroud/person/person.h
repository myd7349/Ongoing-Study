#pragma once

#include <string>

struct Person {
  Person(const char *name, int age)
    : name_(name), age_(age) {}

  const std::string name() const {
    return name_;
  }
  
  int age() const {
    return age_;
  }
  
  static std::string Introduce(const Person &person);

private:
  std::string name_;
  int age_;
};
