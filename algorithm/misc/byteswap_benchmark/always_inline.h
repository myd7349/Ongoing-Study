#pragma once

#ifndef ALWAYS_INLINE
// simdjson/common_defs.h
# ifdef _MSC_VER
#  define ALWAYS_INLINE __forceinline
# else
#  define ALWAYS_INLINE inline __attribute__((always_inline, unused))
# endif
#endif
