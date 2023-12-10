#ifndef TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_DEDUCTION_GUIDE_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_DEDUCTION_GUIDE_HPP

#include TUSTR_COMMON_INCLUDE(fstring/fstring.hpp)

namespace tustr
{
    /**
     * 文字列リテラルによるインスタンス化用の推論補助
    */
    template <std::size_t N, class CharT>
    fstring(const CharT(&)[N])
        -> fstring<N - 1, CharT, std::char_traits<CharT>>;

    /**
     * 文字リテラルによるインスタンス化用の推論補助
    */
    template <class CharT>
    fstring(CharT)
        -> fstring<1, CharT, std::char_traits<CharT>>;
}

#endif
