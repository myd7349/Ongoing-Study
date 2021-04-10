#include "person.h"

#include <iostream>
#include <sstream>


std::string Person::Introduce(const Person &person) {
  std::ostringstream oss;
  oss << "Hi! This is " << person.name()
    << ", and I am " << person.age() << " years old.";
  return oss.str();
}


int main() {
  Person tom("Tom", 18);
  std::cout << Person::Introduce(tom) << std::endl;
  return 0;
}
