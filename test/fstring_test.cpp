#include <gtest/gtest.h>
#include <tustr/fstring.hpp>

template <tustr::basic_fstring S>
struct test_struct { static constexpr auto value = S; };

TEST(TustrFstringTest, ConstructorTest)
{
    tustr::basic_fstring fstr1 {""};
    tustr::basic_fstring fstr2 {L"abcdef"};
    tustr::fstring fstr3 {"abcdefg"};
    constexpr auto fstr4 = test_struct<"efgh">::value;
    constexpr auto fstr5 = test_struct<L"hijklmn">::value;
    constexpr auto fstr6 = test_struct<U"opqr">::value;

    ASSERT_STREQ(fstr1.data(), "");
    ASSERT_STREQ(fstr2.data(), L"abcdef");
    ASSERT_STREQ(fstr3.data(), "abcdefg");
    ASSERT_STREQ(fstr4.data(), "efgh");
    ASSERT_STREQ(fstr5.data(), L"hijklmn");
}

TEST(TustrFstringTest, MemberFunctionsTest)
{
    constexpr tustr::fstring fstr1 {"abcdefg"};
    constexpr tustr::fstring fstr2 {"hijklm"};
    constexpr tustr::fstring fstr3 {"nopqrstu"};
    constexpr auto fstr4 = fstr1.concat(fstr2, fstr3);
    
    ASSERT_STREQ(fstr4.data(), "abcdefghijklmnopqrstu");
}
