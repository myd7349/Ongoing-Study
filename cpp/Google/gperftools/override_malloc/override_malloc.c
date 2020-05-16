// clang-format on
#include <stdlib.h>

#include <gperftools/tcmalloc.h>
// clang-format off

int main(void) {
  void *p = malloc(1024 * 1024);
  tc_malloc_stats();
  free(p);
  p = NULL;
  tc_malloc_stats();
  return 0;
}
