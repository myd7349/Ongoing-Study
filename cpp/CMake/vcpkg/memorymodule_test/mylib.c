#include "mylib.h"

#include <stdio.h>

void Foo(const char *name) {
  printf("Hello, %s!\n", name == NULL ? "stranger" : name);
}
