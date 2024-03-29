#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int arr1[] = {1, 2, 3, 4, 5, 6};
  int arr2[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  int arr3[2][3] = {{1, 2, 3}, {4, 5, 6}};

  printf("%d\n", memcmp(arr1, arr2, sizeof(arr1)));
  printf("%d\n", memcmp(arr1, arr3, sizeof(arr1)));

  // Treat arr1 as a 3x2 array:
  int *rows[3];
  int **buffer = rows;
  for (int i = 0; i < 3; ++i) buffer[i] = &arr1[i * 2];

  buffer[0][0] *= 10;
  buffer[0][1] *= 10;
  buffer[1][0] *= 10;
  buffer[1][1] *= 10;
  buffer[2][0] *= 10;
  buffer[2][1] *= 10;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 2; ++j) printf("%d ", buffer[i][j]);

    putchar('\n');
  }

  return 0;
}

// clang-format off
// References:
// [Writing & Appending arrays of float to the only dataset in hdf5 file in C++](https://stackoverflow.com/questions/15379399/writing-appending-arrays-of-float-to-the-only-dataset-in-hdf5-file-in-c)
//     double **data = malloc(4 * sizeof(double *));
//     data[0] = malloc(100 * sizeof(double));
//     data[1] = malloc(100 * sizeof(double));
//     data[2] = malloc(100 * sizeof(double));
//     data[3] = malloc(100 * sizeof(double));
//     extern void process_data_v1(const double **data);
//     extern void process_data_v2(const double * const *data);
//     process_data_v1(data); // syntax error
//     process_data_v2(data);
// cdecl double **data
// > declare data as pointer to pointer to double
// cdecl const double **data
// > declare data as pointer to pointer to const double
// cdecl const double * const *data
// > declare data as pointer to const pointer to const double
// clang-format on
