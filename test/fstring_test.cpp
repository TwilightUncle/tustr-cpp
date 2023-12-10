#include <gtest/gtest.h>
#include <tustr/fstring.hpp>

template <tustr::basic_fstring S>
struct test_struct { static constexpr auto value = S; };

TEST(Tustrbasic_fstringTest, ConstructorTest)
{
    tustr::basic_fstring fstr1 {""};
    tustr::basic_fstring fstr2 = L"abcdef";
    auto fstr3 = tustr::basic_fstring{"abcdefg"};
    constexpr auto fstr4 = test_struct<"efgh">::value;
    constexpr auto fstr5 = test_struct<L"hijklmn">::value;
    constexpr auto fstr6 = test_struct<U"opqr">::value;
    constexpr auto fstr7 = tustr::basic_fstring{L'b'};
    constexpr auto fstr8 = test_struct<'-'>::value;
    constexpr tustr::basic_fstring fstr9 = {};
    constexpr tustr::basic_fstring fstr10 {};

    ASSERT_STREQ(fstr1.data(), "");
    ASSERT_STREQ(fstr2.data(), L"abcdef");
    ASSERT_STREQ(fstr3.data(), "abcdefg");
    ASSERT_STREQ(fstr4.data(), "efgh");
    ASSERT_STREQ(fstr5.data(), L"hijklmn");
    ASSERT_STREQ(fstr7.data(), L"b");
    ASSERT_STREQ(fstr8.data(), "-");
    ASSERT_STREQ(fstr9.data(), "");
    ASSERT_STREQ(fstr10.data(), "");

    constexpr tustr::fstring cfstr1 = "123";
    constexpr tustr::fstring cfstr2 = {};
    constexpr tustr::fstring cfstr3 = '1';
    constexpr tustr::u8fstring u8fstr1 = u8"123";
    constexpr tustr::u8fstring u8fstr2 = {};
    constexpr tustr::u8fstring u8fstr3 = u8'1';
    constexpr tustr::u16fstring u16fstr1 = u"123";
    constexpr tustr::u16fstring u16fstr2 = {};
    constexpr tustr::u16fstring u16fstr3 = u'1';
    constexpr tustr::u32fstring u32fstr1 = U"123";
    constexpr tustr::u32fstring u32fstr2 = {};
    constexpr tustr::u32fstring u32fstr3 = U'1';
    constexpr tustr::wfstring wfstr1 = L"123";
    constexpr tustr::wfstring wfstr2 = {};
    constexpr tustr::wfstring wfstr3 = L'1';

    ASSERT_STREQ(cfstr1.data(), "123");
    ASSERT_STREQ(cfstr2.data(), "");
    ASSERT_STREQ(cfstr3.data(), "1");
    ASSERT_STREQ(wfstr1.data(), L"123");
    ASSERT_STREQ(wfstr2.data(), L"");
    ASSERT_STREQ(wfstr3.data(), L"1");

}

TEST(Tustrbasic_fstringTest, MemberFunctionsTest)
{
    constexpr tustr::basic_fstring fstr1 {"abcdefg"};
    constexpr tustr::basic_fstring fstr2 {"hijklm"};
    constexpr tustr::basic_fstring fstr3 {"nopqrstu"};
    constexpr auto fstr4 = fstr1.concat(fstr2, fstr3);
    constexpr auto fstr5 = fstr4.remove_prefix<3>()
        .remove_suffix<6>()
        .append("123")
        .append('4')
        .erase<5, 3>();
    
    ASSERT_STREQ(fstr4.data(), "abcdefghijklmnopqrstu");
    ASSERT_STREQ(fstr5.data(), "defghlmno1234");

    constexpr auto wfstr1 = tustr::wfstring{L"123456789"}
        .remove_prefix<2>()
        .remove_suffix<3>()
        .append(L"abcde")
        .erase<3, 4>();

    ASSERT_STREQ(wfstr1.data(), L"345de");
}
