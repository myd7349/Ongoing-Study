#include <gtest/gtest.h>

#include "../data_rate_unit.h"


TEST(DataRateConvertTest, Test_Bps)
{
    EXPECT_EQ(data_rate_convert(1, Bps, bps), 8);
}


TEST(DataRateConvertTest, Test_kbps)
{
    EXPECT_EQ(data_rate_convert(1, kbps, bps), 1000);
    EXPECT_EQ(data_rate_convert(1, kbps, Bps), 125);
}


TEST(DataRateConvertTest, Test_Mbps)
{
    EXPECT_EQ(data_rate_convert(1, Mbps, kbps), 1000);
    EXPECT_EQ(data_rate_convert(1, Mbps, bps), 1000000);
    EXPECT_EQ(data_rate_convert(1, Mbps, Bps), 125000);
    EXPECT_EQ(data_rate_convert(1, Mbps, KBps), 125);
}


TEST(DataRateConvertTest, Test_Gbps)
{
    EXPECT_EQ(data_rate_convert(1, Gbps, Mbps), 1000);
    EXPECT_EQ(data_rate_convert(1, Gbps, kbps), 1000000);
    EXPECT_EQ(data_rate_convert(1, Gbps, bps), 1000000000);
    EXPECT_EQ(data_rate_convert(1, Gbps, Bps), 125000000);
    EXPECT_EQ(data_rate_convert(1, Gbps, MBps), 125);
}


TEST(DataRateConvertTest, Test_Tbps)
{
    EXPECT_EQ(data_rate_convert(1, Tbps, Gbps), 1000);
    EXPECT_EQ(data_rate_convert(1, Tbps, Mbps), 1000000);
    EXPECT_EQ(data_rate_convert(1, Tbps, kbps), 1000000000);
    EXPECT_EQ(data_rate_convert(1, Tbps, bps), 1000000000000);
    EXPECT_EQ(data_rate_convert(1, Tbps, Bps), 125000000000);
    EXPECT_EQ(data_rate_convert(1, Tbps, GBps), 125);
}


#define EXPECT_LONG_DOUBLE_EQ(val1, val2) \
    EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<long double>, val1, val2)


TEST(DataRateConvertFTest, TestF_Bps)
{
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Bps, bps), 8);
}


TEST(DataRateConvertFTest, TestF_kbps)
{
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, kbps, bps), 1000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, kbps, Bps), 125);
}


TEST(DataRateConvertFTest, TestF_Mbps)
{
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Mbps, kbps), 1000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Mbps, bps), 1000000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Mbps, Bps), 125000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Mbps, KBps), 125);
}


TEST(DataRateConvertFTest, TestF_Gbps)
{
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Gbps, Mbps), 1000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Gbps, kbps), 1000000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Gbps, bps), 1000000000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Gbps, Bps), 125000000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Gbps, MBps), 125);
}


TEST(DataRateConvertTest, TestF_Tbps)
{
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Tbps, Gbps), 1000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Tbps, Mbps), 1000000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Tbps, kbps), 1000000000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Tbps, bps), 1000000000000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Tbps, Bps), 125000000000);
    EXPECT_LONG_DOUBLE_EQ(data_rate_convertf(1, Tbps, GBps), 125);
}


TEST(DataRateNameTest, Test_name)
{
    EXPECT_STREQ(data_rate_unit_name(bps), "bps");
    EXPECT_STREQ(data_rate_unit_name(kbps), "kbps");
    EXPECT_STREQ(data_rate_unit_name(Mbps), "Mbps");
    EXPECT_STREQ(data_rate_unit_name(Gbps), "Gbps");
    EXPECT_STREQ(data_rate_unit_name(Tbps), "Tbps");

    EXPECT_STREQ(data_rate_unit_name(Bps), "Bps");
    EXPECT_STREQ(data_rate_unit_name(KBps), "KB/s");
    EXPECT_STREQ(data_rate_unit_name(MBps), "MB/s");
    EXPECT_STREQ(data_rate_unit_name(GBps), "GB/s");
    EXPECT_STREQ(data_rate_unit_name(TBps), "TB/s");

    EXPECT_STREQ(data_rate_unit_name(KiBps), "KiB/s");
    EXPECT_STREQ(data_rate_unit_name(MiBps), "MiB/s");
    EXPECT_STREQ(data_rate_unit_name(GiBps), "GiB/s");
    EXPECT_STREQ(data_rate_unit_name(TiBps), "TiB/s");
}


// References:
// https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
// https://github.com/google/googletest/issues/791
// https://stackoverflow.com/questions/3564871/difference-between-double-comparisons-in-gtest-c-and-nunit-c
// https://github.com/google/googletest/blob/master/googletest/docs/primer.md
