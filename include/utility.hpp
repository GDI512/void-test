#ifndef CPPLTF_UTILITY_HPP
#define CPPLTF_UTILITY_HPP

namespace test {

    using string = const char*;
    using size_type = decltype(sizeof(int));
    using difference_type = decltype(static_cast<int*>(0) - static_cast<int*>(0));

}

namespace test::core {

    struct true_type {
        static constexpr auto value = true;
    };

    struct false_type {
        static constexpr auto value = false;
    };

    template <typename T>
    struct remove_reference {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&> {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&> {
        using type = T;
    };

    template <typename T>
    struct type_identity {
        using type = T;
    };

    template <typename T, typename U>
    struct is_same : false_type {};

    template <typename T>
    struct is_same<T, T> : true_type {};

    template <typename T>
    struct is_lvalue_reference : false_type {};

    template <typename T>
    struct is_lvalue_reference<T&> : true_type {};

    template <typename value_type, auto size>
    constexpr auto begin(value_type (&array)[size]) {
        return static_cast<value_type*>(array);
    }

    template <typename value_type, auto size>
    constexpr auto begin(const value_type (&array)[size]) {
        return static_cast<const value_type*>(array);
    }

    template <typename value_type>
    constexpr decltype(auto) begin(value_type& container) {
        return container.begin();
    }

    template <typename value_type>
    constexpr decltype(auto) begin(const value_type& container) {
        return container.begin();
    }

    template <typename value_type, auto size>
    constexpr auto end(value_type (&array)[size]) {
        return array + size;
    }

    template <typename value_type, auto size>
    constexpr auto end(const value_type (&array)[size]) {
        return array + size;
    }

    template <typename value_type>
    constexpr decltype(auto) end(value_type& container) {
        return container.end();
    }

    template <typename value_type>
    constexpr decltype(auto) end(const value_type& container) {
        return container.end();
    }

    template <typename value_type>
    constexpr decltype(auto) move(value_type&& value) noexcept {
        return static_cast<typename remove_reference<value_type>::type&&>(value);
    }

    template <typename value_type>
    constexpr decltype(auto) forward(typename remove_reference<value_type>::type& value) noexcept {
        return static_cast<value_type&&>(value);
    }

    template <typename value_type>
    constexpr decltype(auto) forward(typename remove_reference<value_type>::type&& value) noexcept {
        static_assert(!is_lvalue_reference<value_type>::value);
        return static_cast<value_type&&>(value);
    }

    template <typename value_type, typename other_type>
    constexpr auto exchange(value_type& value, other_type&& replacement) {
        auto old = core::move(value);
        value = core::forward<other_type>(replacement);
        return old;
    }

    template <typename input, typename invocable>
    constexpr auto is_sorted(input first, input last, invocable comparison) {
        if (first != last) {
            auto next = first;
            while (++next != last) {
                if (!comparison(*first, *next))
                    return false;
                first = next;
            }
        }
        return true;
    }

    template <typename input, typename invocable>
    constexpr auto all_of(input first, input last, invocable predicate) {
        for (; first != last; ++first)
            if (!predicate(*first))
                return false;
        return true;
    }

    template <typename input, typename oinput>
    constexpr auto equal(input first, input last, oinput other) {
        for (; first != last; ++first, ++other)
            if (*first != *other)
                return false;
        return true;
    }

    template <typename input, typename value_type>
    constexpr auto find(input first, input last, const value_type& value) {
        for (; first != last; ++first)
            if (*first == value)
                return first;
        return last;
    }

    template <typename type, auto length>
    class array {
      public:
        using value_type = type;
        using reference = type&;
        using const_reference = const type&;
        using iterator = type*;
        using const_iterator = const type*;

      private:
        value_type data[length];

      public:
        constexpr auto operator[](size_type index) noexcept -> reference { return data[index]; }
        constexpr auto operator[](size_type index) const noexcept -> const_reference { return data[index]; }

      public:
        constexpr auto begin() noexcept -> iterator { return data; }
        constexpr auto begin() const noexcept -> const_iterator { return data; }
        constexpr auto end() noexcept -> iterator { return data + length; }
        constexpr auto end() const noexcept -> const_iterator { return data + length; }
        constexpr auto size() const noexcept -> size_type { return length; }
    };

    auto on_error(string source) noexcept -> bool;
    auto on_success(string source) noexcept -> bool;
    auto on_exception(string source) noexcept -> void;

}

#endif
