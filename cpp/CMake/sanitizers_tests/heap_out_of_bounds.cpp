// RUN: clang -O -g -fsanitize=address %t && ./a.out
int main(int argc, char **argv) {
  int *array = new int[100];
  array[0] = 0;
  int res = array[argc + 100];  // BOOM
  delete [] array;
  return res;
}

// References:
// https://github.com/google/sanitizers/wiki/AddressSanitizerExampleHeapOutOfBounds
