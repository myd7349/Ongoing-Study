#include <stddef.h>
#include <stdio.h>

#include <tinyexpr.h>

#define TINYEXPR_TEST(expr) \
    printf("%s = %f\n", (expr), te_interp((expr), 0))

int main(void) {
  double data[] = { 1000, 99, 32, 255 };
  double x;
  te_variable vars[] = { { "x", &x } };
  int err;
  te_expr *expr = te_compile("x / 1000.0", vars, 1, &err);
  size_t i;

  if (expr) {
    for (i = 0; i < sizeof(data)/sizeof(data[0]); ++i) {
      x = data[i];
      printf("%f / 1000.0 = %f\n", x, te_eval(expr));
    }

    te_free(expr);
  } else {
    printf("Parse error at %d.\n", err);
  }

  TINYEXPR_TEST("1000.0 / 3");
  TINYEXPR_TEST("5 * 5");
  TINYEXPR_TEST("sqrt(2.0)");

  return 0;
}


// References:
// https://github.com/kimwalisch/calculator
