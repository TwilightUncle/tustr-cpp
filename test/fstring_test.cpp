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
    constexpr auto fstr7 = tustr::basic_fstring{L'b'};

    ASSERT_STREQ(fstr1.data(), "");
    ASSERT_STREQ(fstr2.data(), L"abcdef");
    ASSERT_STREQ(fstr3.data(), "abcdefg");
    ASSERT_STREQ(fstr4.data(), "efgh");
    ASSERT_STREQ(fstr5.data(), L"hijklmn");
    ASSERT_STREQ(fstr7.data(), L"b");
}

TEST(TustrFstringTest, MemberFunctionsTest)
{
    constexpr tustr::fstring fstr1 {"abcdefg"};
    constexpr tustr::fstring fstr2 {"hijklm"};
    constexpr tustr::fstring fstr3 {"nopqrstu"};
    constexpr auto fstr4 = fstr1.concat(fstr2, fstr3);
    constexpr auto fstr5 = fstr4.remove_prefix<3>();
    constexpr auto fstr6 = fstr5.remove_suffix<6>();
    
    ASSERT_STREQ(fstr4.data(), "abcdefghijklmnopqrstu");
    ASSERT_STREQ(fstr5.data(), "defghijklmnopqrstu");
    ASSERT_STREQ(fstr6.data(), "defghijklmno");
}
