#include <gtest/gtest.h>
#include <tustr/convert.hpp>

TEST(TustrConvertTest, ToFstringFromIntTest)
{
    constexpr auto case1 = tustr::to_fstring_from_int<12345u>();
    constexpr auto case2 = tustr::to_fstring_from_int<0b1111, 2, wchar_t>();
    constexpr auto case3 = tustr::to_fstring_from_int<-012345, 8>();
    constexpr auto case4 = tustr::to_fstring_from_int<-0xABCDEF, 16>();
    constexpr auto case5 = tustr::to_wfstring_from_int<-0b1010, 2>();

    ASSERT_STREQ(case1.data(), "12345");
    ASSERT_STREQ(case2.data(), L"0b1111");
    ASSERT_STREQ(case3.data(), "-012345");
    ASSERT_STREQ(case4.data(), "-0xABCDEF");
    ASSERT_STREQ(case5.data(), L"-0b1010");
}
