// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/googletest.h#L121-L195
#pragma once

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

using std::exit;
using std::fprintf;
using std::isinf;
using std::isnan;
using std::vector;


#define EXPECT_TRUE(cond)                               \
  do {                                                  \
    if (!(cond)) {                                      \
      fprintf(stderr, "Check failed: %s\n", #cond);     \
      exit(1);                                          \
    }                                                   \
  } while (0)

#define EXPECT_FALSE(cond)  EXPECT_TRUE(!(cond))

#define EXPECT_OP(op, val1, val2)                                       \
  do {                                                                  \
    if (!((val1) op (val2))) {                                          \
      fprintf(stderr, "Check failed: %s %s %s\n", #val1, #op, #val2);   \
      exit(1);                                                          \
    }                                                                   \
  } while (0)

#define EXPECT_EQ(val1, val2)  EXPECT_OP(==, val1, val2)
#define EXPECT_NE(val1, val2)  EXPECT_OP(!=, val1, val2)
#define EXPECT_GT(val1, val2)  EXPECT_OP(>, val1, val2)
#define EXPECT_LT(val1, val2)  EXPECT_OP(<, val1, val2)

#define EXPECT_NAN(arg)                                         \
  do {                                                          \
    if (!isnan(arg)) {                                          \
      fprintf(stderr, "Check failed: isnan(%s)\n", #arg);       \
      exit(1);                                                  \
    }                                                           \
  } while (0)

#define EXPECT_INF(arg)                                         \
  do {                                                          \
    if (!isinf(arg)) {                                          \
      fprintf(stderr, "Check failed: isinf(%s)\n", #arg);       \
      exit(1);                                                  \
    }                                                           \
  } while (0)

#define EXPECT_DOUBLE_EQ(val1, val2)                                    \
  do {                                                                  \
    if (((val1) < (val2) - 0.001 || (val1) > (val2) + 0.001)) {         \
      fprintf(stderr, "Check failed: %s == %s\n", #val1, #val2);        \
      exit(1);                                                          \
    }                                                                   \
  } while (0)

#define EXPECT_STREQ(val1, val2)                                        \
  do {                                                                  \
    if (strcmp((val1), (val2)) != 0) {                                  \
      fprintf(stderr, "Check failed: streq(%s, %s)\n", #val1, #val2);   \
      exit(1);                                                          \
    }                                                                   \
  } while (0)

vector<void(*)()> g_testlist;  // the tests to run

#define TEST(a, b)                                      \
  struct Test_##a##_##b {                               \
    Test_##a##_##b() { g_testlist.push_back(&Run); }    \
    static void Run() { /* FlagSaver fs; */ RunTest(); }      \
    static void RunTest();                              \
  };                                                    \
  static Test_##a##_##b g_test_##a##_##b;               \
  void Test_##a##_##b::RunTest()


static inline int RUN_ALL_TESTS() {
    vector<void(*)()>::const_iterator it;
    for (it = g_testlist.begin(); it != g_testlist.end(); ++it) {
        (*it)();
    }
    fprintf(stderr, "Passed %d tests\n\nPASS\n", (int)g_testlist.size());
    return 0;
}
