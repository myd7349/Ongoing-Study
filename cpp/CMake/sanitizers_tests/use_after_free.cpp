// RUN: clang -O -g -fsanitize=address %t && ./a.out
int main(int argc, char **argv) {
  int *array = new int[100];
  delete [] array;
  return array[argc];  // BOOM
}


// References:
// https://github.com/google/sanitizers/wiki/AddressSanitizerExampleUseAfterFree
