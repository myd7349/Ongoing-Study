#include <assert.h>
#include <stdio.h>

#define STR_IMPL(c) #c
#define STR(c) STR_IMPL(c)

// [start, end)
typedef struct {
  int start;
  int end;
} range_t;

int is_range_valid(const range_t *range) {
  assert(range != NULL);
  return range->start <= range->end;
}

int is_range_overlap(const range_t *lhs, const range_t *rhs) {
  assert(is_range_valid(lhs));
  assert(is_range_valid(rhs));
  return lhs->start < rhs->end && rhs->start < lhs->end;
}

#define TEST(start1, end1, start2, end2) \
do { \
  range_t range_##start1##_##end1 = { start1, end1 }; \
  range_t range_##start2##_##end2 = { start2, end2 }; \
  printf("[" STR(start1) ", " STR(end1) ") vs " "[" STR(start2) ", " STR(end2) "): %d\n", \
    is_range_overlap(&range_##start1##_##end1, &range_##start2##_##end2)); \
} while (0)

/*
lhs:    |    |
rhs: ||
     |    |
     |           |
          ||
          |      |
                 ||
*/

int main(void) {
  TEST(5, 10, 2, 3);
  TEST(5, 10, 2, 6);
  TEST(5, 10, 2, 11);
  TEST(5, 10, 6, 8);
  TEST(5, 10, 6, 12);
  TEST(5, 10, 12, 15);

  return 0;
}

// References:
// [What's the most efficient way to test two integer ranges for overlap?](https://stackoverflow.com/questions/3269434/whats-the-most-efficient-way-to-test-two-integer-ranges-for-overlap)
