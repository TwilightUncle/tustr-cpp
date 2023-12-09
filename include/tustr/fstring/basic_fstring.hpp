#ifndef TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_BASIC_FSTRING_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_BASIC_FSTRING_HPP

#include <stdexcept>
#include <string_view>

namespace tustr
{
    // 固定長文字列
    // 文字列操作メンバ関数は全てオブジェクトを新規作成する
    template <std::size_t N, class CharT, class Traits = std::char_traits<CharT>>
    class basic_fstring
    {
        constexpr void test_not_empty() const noexcept
        {
            static_assert(N > 0, "Cannot be used because it is empty.");
        }

    public:
        template <std::size_t Size>
        using same_char_fstring = basic_fstring<Size, CharT, Traits>;
        using value_type = CharT;
        using traits_type = Traits;
        using iterator = const CharT*;
        using const_iterator = iterator;
        using view_type = std::basic_string_view<CharT, Traits>;
        using std_string_type = std::basic_string<CharT, Traits>;

        static constexpr std::size_t npos = -1;

        constexpr basic_fstring() noexcept {}

        /**
         * 文字列リテラルから basic_fstring を生成
        */
        constexpr basic_fstring(const value_type (&str_literal)[N + 1]) noexcept
        {
            for (auto i = 0; i < N + 1; i++)
                this->_buf[i] = str_literal[i];
            
            // 必ず終端文字が入るようにする
            _buf[N] = value_type();
        }

        constexpr iterator begin() const noexcept { return &_buf[0]; }
        constexpr iterator end() const noexcept { return begin() + N; }
        constexpr const_iterator cbegin() const noexcept { return begin(); }
        constexpr const_iterator cend() const noexcept { return end(); }
        constexpr auto rbegin() const noexcept { return std::reverse_iterator(end()); }
        constexpr auto rend() const noexcept { return std::reverse_iterator(begin()); }
        constexpr auto crbegin() const noexcept { return std::reverse_iterator(cend()); }
        constexpr auto crend() const noexcept { return std::reverse_iterator(cbegin()); }

        constexpr std::size_t size() const noexcept { return N; }
        constexpr std::size_t length() const noexcept { return N; }
        [[nodiscard]] constexpr bool empty() const noexcept { return N == 0; }

        /**
         * basic_string_view への型キャスト
        */
        constexpr operator view_type() const noexcept { return view_type(_buf); }

        /**
         * basic_string への型キャスト
        */
        constexpr operator std_string_type() const noexcept { return std_string_type(_buf); }

        constexpr const value_type& operator[](std::size_t pos) const
        {
            test_not_empty();
            return _buf[pos];
        }
        constexpr const value_type& at(std::size_t pos) const
        {
            test_not_empty();
            if (pos >= N) throw std::out_of_range;
            return _buf[pos];
        }
        constexpr const value_type& front() const noexcept
        {
            test_not_empty();
            return _buf[0];
        }
        constexpr const value_type& back() const noexcept
        {
            test_not_empty();
            return _buf[N - 1];
        }
        constexpr const value_type* data() const noexcept { return _buf; }

        /**
         * 部分文字列を取得
        */
        template <std::size_t Start = 0, std::size_t Len = npos>
        requires (Start <= N)
        constexpr auto substr() const noexcept
        {
            constexpr std::size_t result_size = std::min<std::size_t>(N - Start, Len);
            return make_by_cstr<result_size>(&_buf[Start]);
        }

        /**
         * 先頭から指定の文字数削る
        */
        template <std::size_t Size>
        requires (Size <= N)
        constexpr auto remove_prefix() const noexcept { return substr<Size>(); }

        /**
         * 最後尾から指定の文字数削る
        */
        template <std::size_t Size>
        requires (Size <= N)
        constexpr auto remove_suffix() const noexcept { return substr<0, N - Size>(); }

        /**
         * 複数の basic_fstring を結合
        */
        template <std::size_t... Sizes>
        constexpr auto concat(const same_char_fstring<Sizes>&... strs) const noexcept
        {
            constexpr std::size_t result_size = N + (Sizes + ...);
            auto s = std_string_type(_buf) + (std_string_type(strs) + ...);
            return make_by_cstr<result_size>(s.c_str());
        }

        constexpr int compare(view_type sv) const noexcept { return view_type(this).compare(sv); }

        // 直接呼び出すのは推奨しない
        value_type _buf[N + 1] = {};

    private:
        /**
         * 文字列配列から固定長文字列を生成
        */
        template <std::size_t Size>
        constexpr auto make_by_cstr(const value_type* s) const noexcept
        {
            value_type new_buf[Size + 1] = {};
            for (auto i = 0; s[i] != value_type() && i < Size; i++)
                new_buf[i] = s[i];
            return same_char_fstring<Size>(new_buf);
        }
    };

    // 推論補助
    template <std::size_t N, class CharT>
    basic_fstring(const CharT(&)[N])
        -> basic_fstring<N - 1, CharT, std::char_traits<CharT>>;
}

#endif
