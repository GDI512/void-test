#ifndef CITRINE_UTILITY_HPP
#define CITRINE_UTILITY_HPP

namespace test {

    using string = const char*;

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
    struct is_lvalue_reference : false_type {};

    template <typename T>
    struct is_lvalue_reference<T&> : true_type {};

    template <typename T>
    constexpr decltype(auto) forward(typename remove_reference<T>::type& value) noexcept {
        return static_cast<T&&>(value);
    }

    template <typename T>
    constexpr decltype(auto) forward(typename remove_reference<T>::type&& value) noexcept {
        static_assert(!is_lvalue_reference<T>::value);
        return static_cast<T&&>(value);
    }

    template <typename I, typename F>
    constexpr auto is_sorted(I first, I last, F comparison) {
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

    template <typename I, typename F>
    constexpr auto all_of(I first, I last, F predicate) {
        for (; first != last; ++first)
            if (!predicate(*first))
                return false;
        return true;
    }

    template <typename I, typename J>
    constexpr auto equal(I first, I last, J other) {
        for (; first != last; ++first, ++other)
            if (*first != *other)
                return false;
        return true;
    }

    template <typename I, typename T>
    constexpr auto find(I first, I last, const T& value) {
        for (; first != last; ++first)
            if (*first == value)
                return first;
        return last;
    }

}

#endif
