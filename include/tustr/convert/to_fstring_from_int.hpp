#ifndef TUSTR_INCLUDE_GUARD_TUSTR_CONVERT_TO_FSTRING_FROM_INT_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_CONVERT_TO_FSTRING_FROM_INT_HPP

#include TUSTR_COMMON_INCLUDE(fstring/function.hpp)


namespace tustr
{
    /**
     * 整数型の出力桁数を取得(Hexで指定した進数)
    */
    template <unsigned int Hex = 10>
    requires (Hex >= 2)
    constexpr std::size_t get_digits_from_int(std::integral auto v)
    {
        std::size_t digits = 1;
        for (; v /= static_cast<decltype(v)>(Hex); digits++);
        return digits;
    }

// 邪悪なる 一時的なマクロ関数
#ifndef TUSTR_FUNC_RETURN_STR_LITERAL
#define TUSTR_FUNC_RETURN_STR_LITERAL(size, type_arg_name, traits, str_literal) []() -> tustr::basic_fstring<size, type_arg_name, traits> { \
        if constexpr (std::is_same_v<type_arg_name, wchar_t>) return {(L ## str_literal)}; \
        else if constexpr (std::is_same_v<type_arg_name, char8_t>) return {(u8 ## str_literal)}; \
        else if constexpr (std::is_same_v<type_arg_name, char16_t>) return {(u ## str_literal)}; \
        else if constexpr (std::is_same_v<type_arg_name, char32_t>) return {(U ## str_literal)}; \
        else return {(str_literal)}; \
    }()
#endif

    /**
     * N真数表記の接頭詞を指定
    */
    template <unsigned int Hex, class CharT = char, class Traits = std::char_traits<CharT>>
    requires (Hex == 2)
    constexpr auto get_hex_prefix() { return TUSTR_FUNC_RETURN_STR_LITERAL(2, CharT, Traits, "0b"); }
    template <unsigned int Hex, class CharT = char, class Traits = std::char_traits<CharT>>
    requires (Hex == 8)
    constexpr auto get_hex_prefix() { return TUSTR_FUNC_RETURN_STR_LITERAL(1, CharT, Traits, "0"); }
    template <unsigned int Hex, class CharT = char, class Traits = std::char_traits<CharT>>
    requires (Hex == 16)
    constexpr auto get_hex_prefix() { return TUSTR_FUNC_RETURN_STR_LITERAL(2, CharT, Traits, "0x"); }
    template <unsigned int Hex, class CharT = char, class Traits = std::char_traits<CharT>>
    requires (Hex == 10)
    constexpr auto get_hex_prefix() { return TUSTR_FUNC_RETURN_STR_LITERAL(0, CharT, Traits, ""); }

    /**
     * 整数値を文字列に変換
    */
    template <std::integral auto V, unsigned int Hex = 10, class CharT = char, class Traits = std::char_traits<CharT>>
    requires (V >= 0 && (Hex == 2 || Hex == 8 || Hex == 10 || Hex == 16))
    constexpr auto to_fstring_from_int()
    {
        // constexpr auto hex_prefix = get_hex_prefix<Hex, CharT, Traits>();
        constexpr std::size_t len = get_digits_from_int<Hex>(V);
        constexpr auto code_0 = TUSTR_FUNC_RETURN_STR_LITERAL(1, CharT, Traits, '0')[0];
        constexpr auto code_A = TUSTR_FUNC_RETURN_STR_LITERAL(1, CharT, Traits, 'A')[0];

        tustr::basic_fstring<len, CharT, Traits> s{};
        auto val = V;
        for (auto i = len; i > 0; val /= Hex) {
            const auto code = val % Hex;
            s._buf[--i] = (code < 10)
                ? code_0 + static_cast<CharT>(code)
                : code_A + static_cast<CharT>(code - 10);
        }

        return get_hex_prefix<Hex, CharT, Traits>() + s;
    }
    template <std::integral auto V, unsigned int Hex = 10, class CharT = char, class Traits = std::char_traits<CharT>>
    requires (V < 0)
    constexpr auto to_fstring_from_int() { return  TUSTR_FUNC_RETURN_STR_LITERAL(1, CharT, Traits, '-') + to_fstring_from_int<-V, Hex, CharT, Traits>(); }
    template <std::integral auto V, unsigned int Hex = 10>
    constexpr auto to_wfstring_from_int() { return to_fstring_from_int<V, Hex, wchar_t>(); }
    template <std::integral auto V, unsigned int Hex = 10>
    constexpr auto to_u8fstring_from_int() { return to_fstring_from_int<V, Hex, char8_t>(); }
    template <std::integral auto V, unsigned int Hex = 10>
    constexpr auto to_u16fstring_from_int() { return to_fstring_from_int<V, Hex, char16_t>(); }
    template <std::integral auto V, unsigned int Hex = 10>
    constexpr auto to_u32fstring_from_int() { return to_fstring_from_int<V, Hex, char32_t>(); }

// マクロ削除
#undef TUSTR_FUNC_RETURN_STR_LITERAL
}


#endif
