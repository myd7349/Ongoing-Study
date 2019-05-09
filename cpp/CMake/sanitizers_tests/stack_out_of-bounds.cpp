// RUN: clang -O -g -fsanitize=address %t && ./a.out
int main(int argc, char **argv) {
  int stack_array[100];
  stack_array[1] = 0;
  return stack_array[argc + 100];  // BOOM
}

// References:
// https://github.com/google/sanitizers/wiki/AddressSanitizerExampleStackOutOfBounds
