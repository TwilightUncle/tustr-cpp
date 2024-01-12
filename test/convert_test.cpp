#include <gtest/gtest.h>
#include <tustr/convert.hpp>

TEST(TustrConvertTest, ToFstringFromIntTest)
{
    constexpr auto case1 = tustr::to_fstring_from_int<12345u>();
    constexpr auto case2 = tustr::to_basic_fstring_from_int<0b1111, 2, wchar_t>();
    constexpr auto case3 = tustr::to_fstring_from_int<-012345, 8>();
    constexpr auto case4 = tustr::to_fstring_from_int<-0xABCDEF, 16>();
    constexpr auto case5 = tustr::to_wfstring_from_int<-0b1010, 2>();

    ASSERT_STREQ(case1.data(), "12345");
    ASSERT_STREQ(case2.data(), L"0b1111");
    ASSERT_STREQ(case3.data(), "-012345");
    ASSERT_STREQ(case4.data(), "-0xABCDEF");
    ASSERT_STREQ(case5.data(), L"-0b1010");
}

TEST(TustrConvertTest, ToFstringFromFTest)
{
    constexpr auto case1 = tustr::float_value_info(std::numeric_limits<float>::min());
    constexpr auto case2 = tustr::float_value_info(std::numeric_limits<float>::max());
    constexpr auto case3 = tustr::float_value_info(std::numeric_limits<double>::min());
    constexpr auto case4 = tustr::float_value_info(std::numeric_limits<double>::max());
    ASSERT_EQ(case1.get_e2(), -126);
    ASSERT_EQ(case2.get_e2(), 127);
    ASSERT_EQ(case3.get_e2(), -1022);
    ASSERT_EQ(case4.get_e2(), 1023);
}
