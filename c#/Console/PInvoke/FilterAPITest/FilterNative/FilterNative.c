#include "FilterNative.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

struct FilterContextTag {
  FilterType type;
  int64_t count;
};

FilterContext Filter_init(FilterType type) {
  FilterContext context = NULL;

  if (type != FILTER_50HZ && type != FILTER_75HZ && type != FILTER_100HZ)
    return NULL;

  context = malloc(sizeof(struct FilterContextTag));
  if (context == NULL) return NULL;

  context->type = type;
  context->count = 0;

  return context;
}

void Filter_run_many(FilterContext context, const double *data, int length,
                     double *out) {
  int i;

  assert(context != NULL);
  assert(data != NULL && length > 0 && out != NULL);

  for (i = 0; i < length; ++i)
    out[i] = data[i] + (int)context->type + context->count++;
}

double Filter_run(FilterContext context, double x) {
  Filter_run_many(context, &x, 1, &x);
  return x;
}

void Filter_free(FilterContext *context) {
  if (context != NULL && *context != NULL) {
    free(*context);
    *context = NULL;
  }
}
