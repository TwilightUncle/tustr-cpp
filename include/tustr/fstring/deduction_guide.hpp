#ifndef TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_DEDUCTION_GUIDE_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_DEDUCTION_GUIDE_HPP

#include TUSTR_COMMON_INCLUDE(fstring/alias.hpp)

namespace tustr
{
    /**
     * 文字列リテラルによるインスタンス化用の推論補助
    */
    template <std::size_t N, class CharT>
    basic_fstring(const CharT(&)[N])
        -> basic_fstring<N - 1, CharT, std::char_traits<CharT>>;

    /**
     * 文字リテラルによるインスタンス化用の推論補助
    */
    template <class CharT>
    basic_fstring(CharT)
        -> basic_fstring<1, CharT, std::char_traits<CharT>>;

    /**
     * 一貫した初期化を行うことができるようにデフォルトコンストラクタの場合の推論補助。
     * ひとまず、char。
    */
    basic_fstring() -> basic_fstring<0, char, std::char_traits<char>>;

    // -----------------------------
    // エイリアス用の推論補助
    // -----------------------------

    template <std::size_t N>
    fstring(const char(&)[N]) -> fstring<N - 1>;
    fstring() -> fstring<0>;

    template <std::size_t N>
    u8fstring(const char8_t(&)[N]) -> u8fstring<N - 1>;
    u8fstring() -> u8fstring<0>;

    template <std::size_t N>
    u16fstring(const char16_t(&)[N]) -> u16fstring<N - 1>;
    u16fstring() -> u16fstring<0>;

    template <std::size_t N>
    u32fstring(const char32_t(&)[N]) -> u32fstring<N - 1>;
    u32fstring() -> u32fstring<0>;

    template <std::size_t N>
    wfstring(const wchar_t(&)[N]) -> wfstring<N - 1>;
    wfstring() -> wfstring<0>;
}

#endif
