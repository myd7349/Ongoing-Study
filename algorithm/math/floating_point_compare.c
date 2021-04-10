#include "floating_point_compare.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>

// -- googletest/include/gtest/internal/gtest-internal.h --
// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
typedef double RawType;

typedef uint64_t Bits;

#define kBitCount (8 * sizeof(RawType))

// # of fraction bits in a number.
#define kFractionBitCount ((size_t)(DBL_MANT_DIG - 1))

// # of exponent bits in a number.
#define kExponentBitCount ((size_t)(kBitCount - 1 - kFractionBitCount))

// The mask for the sign bit.
#define kSignBitMask ((Bits)(((Bits)1) << (kBitCount - 1)))

// The mask for the fraction bits.
#define kFractionBitMask ((Bits)(~(Bits)(0) >> (kExponentBitCount + 1)))

// The mask for the exponent bits.
#define kExponentBitMask ((Bits) ~(kSignBitMask | kFractionBitMask))

// How many ULP's (Units in the Last Place) we want to tolerate when
// comparing two numbers.  The larger the value, the more error we
// allow.  A 0 value means that two numbers must be exactly the same
// to be considered equal.
//
// The maximum error of a single floating-point operation is 0.5
// units in the last place.  On Intel CPU's, all floating-point
// calculations are done with 80-bit precision, while double has 64
// bits.  Therefore, 4 should be enough for ordinary use.
//
// See the following article for more details on ULP:
// http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
#define kMaxUlps ((size_t)4)

union FloatingPointUnion {
  RawType value_;  // The raw floating-point number.
  Bits bits_;      // The bits that represent the number.
};

// Reinterprets a bit pattern as a floating-point number.
//
// This function is needed to test the AlmostEquals() method.
static RawType reinterpret_bits(Bits bits) {
  union FloatingPointUnion fp = {0};
  fp.bits_ = bits;
  return fp.value_;
}

// Returns the floating-point number that represent positive infinity.
static RawType infinity() { return reinterpret_bits(kExponentBitMask); }

// Returns the bits that represents this number.
static Bits get_bits(union FloatingPointUnion fp) { return fp.bits_; }

// Returns the exponent bits of this number.
static Bits exponent_bits(union FloatingPointUnion fp) {
  return kExponentBitMask & fp.bits_;
}

// Returns the fraction bits of this number.
static Bits fraction_bits(union FloatingPointUnion fp) {
  return kFractionBitMask & fp.bits_;
}

// Returns the sign bit of this number.
static Bits sign_bit(union FloatingPointUnion fp) {
  return kSignBitMask & fp.bits_;
}

// Returns true if and only if this is NAN (not a number).
static int is_nan(union FloatingPointUnion fp) {
  // It's a NAN if the exponent bits are all ones and the fraction
  // bits are not entirely zeros.
  return (exponent_bits(fp) == kExponentBitMask) && (fraction_bits(fp) != 0);
}

// Converts an integer from the sign-and-magnitude representation to
// the biased representation.  More precisely, let N be 2 to the
// power of (kBitCount - 1), an integer x is represented by the
// unsigned number x + N.
//
// For instance,
//
//   -N + 1 (the most negative number representable using
//          sign-and-magnitude) is represented by 1;
//   0      is represented by N; and
//   N - 1  (the biggest number representable using
//          sign-and-magnitude) is represented by 2N - 1.
//
// Read http://en.wikipedia.org/wiki/Signed_number_representations
// for more details on signed number representations.
static Bits sign_and_magnitude_to_biased(Bits sam) {
  if (kSignBitMask & sam) {
    // sam represents a negative number.
    return ~sam + 1;
  } else {
    // sam represents a positive number.
    return kSignBitMask | sam;
  }
}

// Given two numbers in the sign-and-magnitude representation,
// returns the distance between them as an unsigned number.
static Bits distance_between_sign_and_magnitude_numbers(Bits sam1, Bits sam2) {
  Bits biased1 = sign_and_magnitude_to_biased(sam1);
  Bits biased2 = sign_and_magnitude_to_biased(sam2);
  return (biased1 >= biased2) ? (biased1 - biased2) : (biased2 - biased1);
}

// Returns true if and only if this number is at most kMaxUlps ULP's away
// from rhs.  In particular, this function:
//
//   - returns false if either number is (or both are) NAN.
//   - treats really large numbers as almost equal to infinity.
//   - thinks +0.0 and -0.0 are 0 DLP's apart.
static int almost_equals(union FloatingPointUnion lhs,
                         union FloatingPointUnion rhs) {
  // The IEEE standard says that any comparison operation involving
  // a NAN must return false.
  if (is_nan(lhs) || is_nan(rhs)) return 0;

  return distance_between_sign_and_magnitude_numbers(lhs.bits_, rhs.bits_) <=
         kMaxUlps;
}
// -- googletest/include/gtest/internal/gtest-internal.h --

int double_almost_equal(double x, double y) {
  union FloatingPointUnion lhs;
  union FloatingPointUnion rhs;

  if (x == y) return 1;

  lhs.value_ = x;
  rhs.value_ = y;

  return almost_equals(lhs, rhs);
}

double get_epsilon(double x) {
  double epsilon = EPSILON;

  x = fabs(x);
  if (x <= 1.0) epsilon = x * EPSILON;

  return epsilon;
}

int double_almost_equal_v2(double x, double y, double epsilon) {
  double delta;
  assert(epsilon >= 0.0);
  if (x == y) return 1;
  delta = x > y ? x - y : y - x;
  return delta <= epsilon;
}

// clang-format off
// References:
// [What is the most effective way for float and double comparison?](https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison)
// [Difference between double comparisons in gtest (C++) and nunit
// (C#)](https://stackoverflow.com/questions/3564871/difference-between-double-comparisons-in-gtest-c-and-nunit-c)
// https://github.com/google/googletest/blob/aee0f9d9b5b87796ee8a0ab26b7587ec30e8858e/googletest/include/gtest/internal/gtest-internal.h#L249-L397
// https://www.zhihu.com/question/32304267
// https://github.com/adevress/hadoken/blob/master/include/hadoken/numeric/float.hpp
// clang-format on
