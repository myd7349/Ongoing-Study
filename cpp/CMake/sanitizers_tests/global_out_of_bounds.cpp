// RUN: clang -O -g -fsanitize=address %t && ./a.out
int global_array[100] = {-1};
int main(int argc, char **argv) {
  return global_array[argc + 100];  // BOOM
}

// References:
// https://github.com/google/sanitizers/wiki/AddressSanitizerExampleGlobalOutOfBounds
