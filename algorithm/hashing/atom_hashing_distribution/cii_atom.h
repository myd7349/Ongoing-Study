// This file is modified from: https://github.com/drh/cii/blob/master/include/atom.h
#ifndef ATOM_INCLUDED
#define ATOM_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef const void *Atom_t;

extern const char *Atom_new(const char *str, int len);
extern const char *Atom_string(const char *str);
extern const char *Atom_int(long n);
extern       int   Atom_length(const char *str);

int Atom_contains(const char *str);
void Atom_free(const char *str); // Free input atom
void Atom_reset(void);

size_t Atom_bench_buckets_size(void);
int    Atom_bench_bucket_len(size_t bucket_no);

#ifdef __cplusplus
}
#endif

#endif
