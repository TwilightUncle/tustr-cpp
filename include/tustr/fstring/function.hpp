#ifndef TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_FUNCTION_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_FUNCTION_HPP

#include TUSTR_COMMON_INCLUDE(fstring/alias.hpp)

namespace tustr
{
    // -------------------------------
    // 型判定用メタ関数
    // -------------------------------

    /**
     * fstring であるか判定
    */
    template <class T>
    struct is_fstring : public std::false_type {};

    template <std::size_t N, class CharT, class Traits>
    struct is_fstring<basic_fstring<N, CharT, Traits>> : public std::true_type {};
    template <std::size_t N>
    struct is_fstring<fstring<N>> : public std::true_type {};
    template <std::size_t N>
    struct is_fstring<u8fstring<N>> : public std::true_type {};
    template <std::size_t N>
    struct is_fstring<u16fstring<N>> : public std::true_type {};
    template <std::size_t N>
    struct is_fstring<u32fstring<N>> : public std::true_type {};
    template <std::size_t N>
    struct is_fstring<wfstring<N>> : public std::true_type {};

    /**
     * fstring であるか判定
    */
    template <class T>
    constexpr bool is_fstring_v = is_fstring<T>::value;

    template <class T>
    concept TustrFstring = is_fstring_v<T>;

    /**
     * 指定の 文字フォーマットの fstring型 か判定
    */
    template <class T, class CharT, class Traits = std::char_traits<CharT>>
    struct eq_fstring_char : public std::false_type {};

    template <TustrFstring T, class CharT, class Traits>
    struct eq_fstring_char<T, CharT, Traits> : public std::is_base_of<
        basic_fstring<T::size(), CharT, Traits>, T
    > {};

    /**
     * 指定の 文字フォーマットの fstring型 か判定
    */
    template <class T, class CharT, class Traits = std::char_traits<CharT>>
    constexpr bool eq_fstring_char_v = eq_fstring_char<T, CharT, Traits>::value;

    /**
     * 2 つのfstringの文字フォーマットが一致するか判定
    */
    template <class T1, class T2>
    struct is_same_char_fstring : public std::false_type {};

    template <TustrFstring T1, class T2>
    struct is_same_char_fstring<T1, T2> : public eq_fstring_char<
        T2, typename T1::value_type, typename T1::traits_type
    > {};

    /**
     * 2 つのfstringの文字フォーマットが一致するか判定
    */
    template <class T1, class T2>
    constexpr bool is_same_char_fstring_v = is_same_char_fstring<T1, T2>::value;

    // -------------------------------
    // 非メンバ関数
    // -------------------------------

    template <std::size_t N1, std::size_t N2, class CharT, class Traits>
    constexpr auto operator+(const basic_fstring<N1, CharT, Traits>& s1, const basic_fstring<N2, CharT, Traits>& s2)
    { return s1.append(s2); }

    template <std::size_t N1, std::size_t N2, class CharT, class Traits>
    constexpr auto operator+(const basic_fstring<N1, CharT, Traits>& s1, const CharT(&s2)[N2])
    { return s1.append(s2); }

    template <std::size_t N1, std::size_t N2, class CharT, class Traits>
    constexpr auto operator+(const CharT(&s1)[N1], const basic_fstring<N2, CharT, Traits>& s2)
    { return operator+(basic_fstring(s1), s2); }

    template <std::size_t N, class CharT, class Traits>
    constexpr auto operator+(const basic_fstring<N, CharT, Traits>& s, CharT c)
    { return s.append(c); }
    
    template <std::size_t N, class CharT, class Traits>
    constexpr auto operator+(CharT c, const basic_fstring<N, CharT, Traits>& s)
    { return operator+(basic_fstring(c), s); }
}

#endif
