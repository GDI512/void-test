#ifndef CITRINE_UTILITY_HPP
#define CITRINE_UTILITY_HPP

namespace citrine {

    using string = const char*;

    using size_type = decltype(sizeof(int));

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

    template <typename iterator, typename invocable>
    constexpr auto is_sorted(iterator first, iterator last, invocable comparison) {
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

    template <typename iterator, typename invocable>
    constexpr auto all_of(iterator first, iterator last, invocable predicate) {
        for (; first != last; ++first)
            if (!predicate(*first))
                return false;
        return true;
    }

    template <typename iterator, typename other_iterator>
    constexpr auto equal(iterator first, iterator last, other_iterator start) {
        for (; first != last; ++first, ++start)
            if (*first != *start)
                return false;
        return true;
    }

    template <typename iterator, typename T>
    constexpr auto find(iterator first, iterator last, const T& value) {
        for (; first != last; ++first)
            if (*first == value)
                return first;
        return last;
    }

}

#endif
