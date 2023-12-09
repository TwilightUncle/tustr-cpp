#ifndef TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_HPP

#ifndef TUSTR_COMMON_INCLUDE
#define TUSTR_COMMON_INCLUDE(path) <tustr/path>
#endif

#include TUSTR_COMMON_INCLUDE(fstring/basic_fstring.hpp)

namespace tustr
{
    template <std::size_t N>
    using fstring = basic_fstring<N, char>;
    template <std::size_t N>
    using wfstring = basic_fstring<N, wchar_t>;
    template <std::size_t N>
    using u8fstring = basic_fstring<N, char8_t>;
    template <std::size_t N>
    using u16fstring = basic_fstring<N, char16_t>;
    template <std::size_t N>
    using u32fstring = basic_fstring<N, char32_t>;
}

#endif
