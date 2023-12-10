#ifndef TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_ALIAS_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_ALIAS_HPP

#include TUSTR_COMMON_INCLUDE(fstring/basic_fstring.hpp)

namespace tustr
{
    template <std::size_t N>
    class fstring : public basic_fstring<N, char> { using basic_fstring<N, char>::basic_fstring; };
    template <std::size_t N>
    class u8fstring : public basic_fstring<N, char8_t> { using basic_fstring<N, char8_t>::basic_fstring; };
    template <std::size_t N>
    class u16fstring : public basic_fstring<N, char16_t> { using basic_fstring<N, char16_t>::basic_fstring; };
    template <std::size_t N>
    class u32fstring : public basic_fstring<N, char32_t> { using basic_fstring<N, char32_t>::basic_fstring; };
    template <std::size_t N>
    class wfstring : public basic_fstring<N, wchar_t> { using basic_fstring<N, wchar_t>::basic_fstring; };
}

#endif
