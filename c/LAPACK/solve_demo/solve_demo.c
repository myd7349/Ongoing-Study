#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <clapack.h>
#include <f2c.h>
#include <openblas/cblas.h>

void swap_i(int *x, int *y) {
  int v;

  assert(x != NULL);
  assert(y != NULL);

  v = *x;
  *x = *y;
  *y = v;
}

void matrix_product_d(const double *a, int a_rows, int a_cols, const double *b,
                      int b_rows, int b_cols, double *c, bool transpose_a,
                      bool transpose_b, double alpha, double beta) {
  int lda = a_cols;
  int ldb = b_cols;

  assert(a != NULL && a_rows > 0 && a_cols > 0);
  assert(b != NULL && b_rows > 0 && b_cols > 0);
  assert(c != NULL);

  if (transpose_a) swap_i(&a_rows, &a_cols);

  if (transpose_b) swap_i(&b_rows, &b_cols);

  assert(a_cols == b_rows);

#define TRANSPOSE(X) ((X) ? CblasTrans : CblasNoTrans)

  // C = alpha*A*B + beta*C
  cblas_dgemm(CblasRowMajor, TRANSPOSE(transpose_a), TRANSPOSE(transpose_b),
              a_rows, b_cols, a_cols, alpha, a, lda, b, ldb, beta, c, b_cols);

#undef TRANSPOSE
}

void easy_matrix_product_d(const double *a, int a_rows, int a_cols,
                           const double *b, int b_rows, int b_cols, double *c) {
  matrix_product_d(a, 2, 2, b, 2, 1, c, false, false, 1.0, 0.0);
}

int main(void) {
  double a[] = {3., 1., 1., 2.};
  double b[] = {2., 3.};
  double c[2];
  size_t i;

  easy_matrix_product_d(a, 2, 2, b, 2, 1, c);

  for (i = 0; i < 2; ++i) printf("%f\n", c[i]);

  return 0;
}

// References:
// https://software.intel.com/en-us/mkl-developer-reference-c-cblas-dot
// http://www.netlib.org/lapack/explore-html/de/da4/group__double__blas__level1_ga75066c4825cb6ff1c8ec4403ef8c843a.html#ga75066c4825cb6ff1c8ec4403ef8c843a
// https://www.konda.eu/c-openblas-matrix-multiplication/
// https://github.com/xianyi/OpenBLAS/wiki/User-Manual
// https://blog.csdn.net/zhikangfu/article/details/78258393
// https://github.com/numpy/numpy/blob/fae5473ee1569011cf56eda9d6f3a5067258b3ec/numpy/linalg/linalg.py#L323-L401
// https://stackoverflow.com/questions/36063993/lapack-dgetrs-vs-dgesv
// https://www.cnblogs.com/Frandy/archive/2011/05/19/LAPACK_Linear_Eq_Solving.html
// https://stackoverflow.com/questions/26875415/difference-between-lapacke-and-lapack
