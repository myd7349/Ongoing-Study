#ifndef ATOM_INCLUDED
#define ATOM_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    extern       int   Atom_length(const char *str);
    extern const char *Atom_new(const char *str, int len);
    extern const char *Atom_string(const char *str);
    extern const char *Atom_int(long n);

    size_t Atom_bench_buckets_size(void);
    int    Atom_bench_bucket_len(size_t bucket_no);

#ifdef __cplusplus
}
#endif

#endif
