#include <stdio.h>
#include <stdlib.h>

#include "../../algutils.h"
#include "../mathutils.h"

int main(void) {
  double u[] = {2, 6, 4};
  double v[] = {1, 2, 5, 4, 8};
  double result[ARRAYSIZE(u) + ARRAYSIZE(v) - 1] = {0};

  convd(ARRAY(u), ARRAY(v), result);
  printvdnl(ARRAY(result));

  return 0;
}
