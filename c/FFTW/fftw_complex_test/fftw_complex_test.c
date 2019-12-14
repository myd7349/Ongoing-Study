#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *fftw_malloc(size_t size) { return calloc(1, size); }

void fftw_free(void *ptr) { free(ptr); }

typedef double fftw_complex[2];

void fftw_enqueue(fftw_complex *in, size_t in_length, const double *data,
                  size_t length) {
  if (length <= 0) return;

  if (length > in_length) length = in_length;

  if (length < in_length)
    memmove(in, in + length, (in_length - length) * sizeof(fftw_complex));

  for (size_t i = in_length - length; i < in_length; ++i)
    in[i][0] = data[i - (in_length - length)];
}

int main(void) {
  double data[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};
  const size_t LENGTH = 10;
  fftw_complex *in = fftw_malloc(LENGTH * sizeof(fftw_complex));

  size_t i, j;

  if (in != NULL) {
    printf("%p, %p\n", in, in + 1);

    for (i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
      fftw_enqueue(in, LENGTH, data + i, 1);

      puts("----------------------------------------");

      for (j = 0; j < LENGTH; ++j) printf("(%.0f, %.0f) ", in[j][0], in[j][1]);

      puts("");
    }
  }

  fftw_free(in);
  return 0;
}
