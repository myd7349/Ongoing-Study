#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FilterContextTag *FilterContext;

typedef enum {
  FILTER_50HZ = 50,
  FILTER_75HZ = 75,
  FILTER_100HZ = 100,
} FilterType;

#ifdef _WIN32
#define FILTER_API_EXPORT __declspec(dllexport)
#else
#define FILTER_API_EXPORT
#endif

FILTER_API_EXPORT FilterContext Filter_init(FilterType type);
FILTER_API_EXPORT void Filter_run_many(FilterContext context,
                                       const double *data, int length,
                                       double *out);
FILTER_API_EXPORT double Filter_run(FilterContext context, double x);
FILTER_API_EXPORT void Filter_free(FilterContext *context);

#ifdef __cplusplus
}
#endif
