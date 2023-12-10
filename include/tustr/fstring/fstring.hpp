#ifndef TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_FSTRING_HPP
#define TUSTR_INCLUDE_GUARD_TUSTR_FSTRING_FSTRING_HPP

#include <stdexcept>
#include <string_view>

namespace tustr
{
    // 固定長文字列。
    // 文字列操作メンバ関数は全て新規オブジェクト作成する。
    // 実行時において、メンバ変数 _buf に直接触れない限りイミュータブル。
    template <std::size_t N, class CharT, class Traits = std::char_traits<CharT>>
    class fstring
    {
        static constexpr void test_not_empty() noexcept
        {
            static_assert(N > 0, "Cannot be used because it is empty.");
        }

    public:
        // -------------------------------
        // メンバ型
        // -------------------------------

        /**
         * サイズだけ異なる fstring
        */
        template <std::size_t Size>
        using same_char_fstring = fstring<Size, CharT, Traits>;

        using value_type = CharT;
        using traits_type = Traits;
        using iterator = const CharT*;
        using const_iterator = iterator;
        using view_type = std::basic_string_view<CharT, Traits>;
        using std_string_type = std::basic_string<CharT, Traits>;

        // -------------------------------
        // メンバ変数
        // -------------------------------

        static constexpr std::size_t npos = -1;

        // 直接呼び出すのは推奨しない
        value_type _buf[N + 1] = {};

        // -------------------------------
        // コンストラクタ
        // -------------------------------

        constexpr fstring() noexcept {}

        /**
         * 文字列リテラルから fstring を生成
        */
        constexpr fstring(const value_type (&str_literal)[N + 1]) noexcept
        {
            for (auto i = 0; i < N + 1; i++)
                this->_buf[i] = str_literal[i];
            
            // 必ず終端文字が入るようにする
            _buf[N] = value_type();
        }

        /**
         * 文字から fstring を生成
        */
        constexpr fstring(value_type c) noexcept
        {
            static_assert(N == 1, "Only size is 1.");
            _buf[0] = c;
        }

        // -------------------------------
        // イテレータ
        // -------------------------------

        constexpr iterator begin() const noexcept { return &_buf[0]; }
        constexpr iterator end() const noexcept { return begin() + N; }
        constexpr const_iterator cbegin() const noexcept { return begin(); }
        constexpr const_iterator cend() const noexcept { return end(); }
        constexpr auto rbegin() const noexcept { return std::reverse_iterator(end()); }
        constexpr auto rend() const noexcept { return std::reverse_iterator(begin()); }
        constexpr auto crbegin() const noexcept { return std::reverse_iterator(cend()); }
        constexpr auto crend() const noexcept { return std::reverse_iterator(cbegin()); }

        // -------------------------------
        // 状態取得・判定
        // -------------------------------

        constexpr std::size_t size() const noexcept { return N; }
        constexpr std::size_t length() const noexcept { return N; }
        [[nodiscard]] constexpr bool empty() const noexcept { return N == 0; }
        constexpr int compare(view_type sv) const noexcept { return view_type(this).compare(sv); }

        // -------------------------------
        // 型キャスト
        // -------------------------------

        /**
         * basic_string_view への型キャスト
        */
        constexpr operator view_type() const noexcept { return view_type(_buf); }

        /**
         * basic_string への型キャスト
        */
        constexpr operator std_string_type() const { return std_string_type(_buf); }

        // -------------------------------
        // 要素アクセス
        // -------------------------------

        constexpr const value_type& operator[](std::size_t pos) const
        {
            test_not_empty();
            return _buf[pos];
        }
        constexpr const value_type& at(std::size_t pos) const
        {
            test_not_empty();
            if (pos >= N) throw std::out_of_range("Specified 'pos' is not exists index.");
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

        // -------------------------------
        // 文字列操作
        // -------------------------------

        /**
         * 部分文字列を返却
        */
        template <std::size_t Start = 0, std::size_t Len = npos>
        requires (Start <= N)
        constexpr auto substr() const noexcept
        {
            constexpr std::size_t result_size = std::min<std::size_t>(N - Start, Len);
            return make_by_cstr<result_size>(&_buf[Start]);
        }

        /**
         * 先頭から指定の文字数削った文字列を返却
        */
        template <std::size_t Size>
        requires (Size <= N)
        constexpr auto remove_prefix() const noexcept { return substr<Size>(); }

        /**
         * 最後尾から指定の文字数削った文字列を返却
        */
        template <std::size_t Size>
        requires (Size <= N)
        constexpr auto remove_suffix() const noexcept { return substr<0, N - Size>(); }

        /**
         * 指定の位置に固定長文字列、文字列リテラル、文字を挿入した文字列を返却。
         * 引数 pos > N の場合、pos の値は N に書き換えられる。
        */
        template <std::size_t Size>
        constexpr auto insert(std::size_t pos, const same_char_fstring<Size>& s) const noexcept
        {
            constexpr auto new_size = N + Size;
            // 未定義領域を踏まないように
            const auto _pos = (std::min)(pos, N);
            value_type new_buf[new_size + 1] = {};
            for (int i = 0; i < _pos; i++) new_buf[i] = _buf[i];
            for (int i = 0; i < Size; i++) new_buf[i + _pos] = s[i];
            for (int i = _pos; i < N; i++) new_buf[i + Size] = _buf[i];
            return same_char_fstring<new_size>(new_buf);
        }
        template <std::size_t Size>
        requires (Size > 0)
        constexpr auto insert(std::size_t pos, const value_type (&str_literal)[Size]) const noexcept
        { return insert(pos, same_char_fstring<Size - 1>(str_literal)); }
        constexpr auto insert(std::size_t pos, value_type c) const noexcept { return insert(pos, same_char_fstring<1>(c)); }

        /**
         * 複数の fstring を結合した文字列を返却
        */
        template <std::size_t Size, std::size_t... Sizes>
        constexpr auto concat(
            const same_char_fstring<Size>& str,
            const same_char_fstring<Sizes>&... strs
        ) const noexcept {
            return insert(N, str).concat(strs...);
        }
        constexpr auto concat() const noexcept { return fstring(*this); }

        /**
         * 固定長文字列、文字列リテラル、文字を末尾に追加した文字列を返却
        */
        template <std::size_t Size>
        constexpr auto append(const same_char_fstring<Size>& s) const noexcept { return concat(s); }
        template <std::size_t Size>
        requires (Size > 0)
        constexpr auto append(const value_type (&str_literal)[Size]) const noexcept
        { return append(same_char_fstring<Size - 1>(str_literal)); }
        constexpr auto append(value_type c) const noexcept { return append(same_char_fstring<1>(c)); }

        /**
         * 末尾に一文字追加した文字列を返却
        */
        constexpr auto push_back(value_type c) const noexcept { return append(c); }

        /**
         * 末尾の一文字を削除
        */
        constexpr auto pop_back() const noexcept
        {
            test_not_empty();
            return remove_suffix<1>();
        }
        
        /**
         * 指定範囲の文字列を削除した文字列を返却
        */
        template <std::size_t Pos, std::size_t Len>
        requires (Pos <= N)
        constexpr auto erase() const noexcept
        {
            constexpr std::size_t erase_end_pos = std::min<std::size_t>(N, Pos + Len);
            return substr<0, Pos>()
                .concat(substr<erase_end_pos>());
        }

        // 型として一貫できないと思われるため、下記メンバ関数の実装はなし。
        // 外部関数として実行する想定
        // * replace 
        //     文字が存在する場合置き換える。
        //     格納している文字列の内容によって結果の文字列長が変動してしまう。
        // * split
        //     指定の文字列により、元の文字を分割する。
        //     格納している文字列の内容によって結果の型が変動してしまう。

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
}

#endif
