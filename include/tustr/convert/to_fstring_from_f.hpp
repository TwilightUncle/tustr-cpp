#ifndef TUSTR_INCLUDE_GUARD_TUSTR_CONVERT_TO_FSTRING_FROM_F_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_CONVERT_TO_FSTRING_FROM_F_HPP

#include <bit>
#include <limits>
#include <type_traits>
#include <tuple>
#include TUSTR_COMMON_INCLUDE(fstring/function.hpp)

namespace tustr
{
    // Sizeで指定した大きさの符号なし整数型を取得する
    template <int ByteSize> struct get_uint;
    template <> struct get_uint<(1 << 0)> : public std::type_identity<std::uint8_t> {};
    template <> struct get_uint<(1 << 1)> : public std::type_identity<std::uint16_t> {};
    template <> struct get_uint<(1 << 2)> : public std::type_identity<std::uint32_t> {};
    template <> struct get_uint<(1 << 3)> : public std::type_identity<std::uint64_t> {};

    template <int ByteSize>
    using get_uint_t = typename get_uint<ByteSize>::type;

    // 浮動小数点型の内部表現とか
    template <std::floating_point T>
    struct float_value_info
    {
        static constexpr int byte_size = sizeof(T);
        static constexpr int bit_length = byte_size << 3;

        using bit_store_t = get_uint_t<byte_size>;
        using int_t = std::make_signed_t<bit_store_t>;

        // IEEE 754の規格を前提とし、倍々精度以上は対応しないものとする
        // ※倍々精度以上のビット列を格納可能な多倍長整数のようなものを定義していないため
        // ※コンパイル時処理可能な多倍長整数を実装したら64以下の条件を撤廃する
        static_assert(std::numeric_limits<T>::is_iec559, "Only support IEEE 754.");
        static_assert(bit_length <= 64, "Only sizes within 64 bits are supported.");

        // 仮数部の2進数桁数
        static constexpr auto mantissa_digits = std::numeric_limits<T>::digits - 1;
        // それぞれ、符号部、仮数部、指数部を抽出するビットマスク
        static constexpr bit_store_t sign_mask = bit_store_t(1) << (bit_length - 1);
        static constexpr bit_store_t mantissa_mask = ~((~bit_store_t(0)) << mantissa_digits);
        static constexpr bit_store_t exponent_mask = ~(sign_mask | mantissa_mask);
        // 指数にかかるバイアス。指数部の先頭ビットのみ0とし、それ以外すべてのビットを立てたもの
        static constexpr int_t exponent_bias = exponent_mask >> (mantissa_digits + 1);

        T _v{};

        constexpr float_value_info(T v) noexcept
            : _v(v)
        {}

        constexpr T get_value() const noexcept { return _v; }
        constexpr auto get_exponent2() const noexcept
        {
            return !get_exponent_bits()
                ? int_t(1) - exponent_bias
                : int_t(get_exponent_bits()) - exponent_bias;
        }

        constexpr bit_store_t get_bits() const noexcept { return std::bit_cast<bit_store_t, T>(_v); }
        constexpr int_t get_sign() const noexcept { return bool(get_bits() & sign_mask) ? -1 : 1; }
        constexpr int_t get_exponent_bits() const noexcept { return (get_bits() & exponent_mask) >> mantissa_digits; }
        constexpr bit_store_t get_mantissa_bits() const noexcept { return get_bits() & mantissa_mask; }

        constexpr bool is_finite() const noexcept { return (get_bits() & exponent_mask) != exponent_mask; }
        constexpr bool is_nan() const noexcept { return !is_finite() && get_mantissa_bits() != 0; }
        constexpr bool is_inf() const noexcept { return !is_finite() && get_mantissa_bits() == 0; }
    };
}

#endif
