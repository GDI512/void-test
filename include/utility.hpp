#ifndef CPPLTF_UTILITY_HPP
#define CPPLTF_UTILITY_HPP

#include "type_traits.hpp"

namespace test {

    using size_type = traits::size_type::type;
    using difference_type = traits::difference_type::type;

    template <typename T>
    constexpr auto begin(T& container) -> decltype(container.begin()) {
        return container.begin();
    }

    template <typename T>
    constexpr auto begin(const T& container) -> decltype(container.begin()) {
        return container.begin();
    }

    template <typename T, auto N>
    constexpr auto begin(T (&array)[N]) -> T* {
        return static_cast<T*>(array);
    }

    template <typename T, auto N>
    constexpr auto begin(const T (&array)[N]) -> const T* {
        return static_cast<const T*>(array);
    }

    template <typename T>
    constexpr auto end(T& container) -> decltype(container.end()) {
        return container.end();
    }

    template <typename T>
    constexpr auto end(const T& container) -> decltype(container.end()) {
        return container.end();
    }

    template <typename T, auto N>
    constexpr auto end(T (&array)[N]) -> T* {
        return array + N;
    }

    template <typename T, auto N>
    constexpr auto end(const T (&array)[N]) -> const T* {
        return array + N;
    }

    template <typename T>
    constexpr auto move(T&& value) noexcept -> typename traits::remove_reference<T>::type&& {
        return static_cast<typename traits::remove_reference<T>::type&&>(value);
    }

    template <typename T>
    constexpr auto forward(typename traits::remove_reference<T>::type& value) noexcept -> T&& {
        return static_cast<T&&>(value);
    }

    template <typename T>
    constexpr auto forward(typename traits::remove_reference<T>::type&& value) noexcept -> T&& {
        static_assert(!traits::is_lvalue_reference<T>::value);
        return static_cast<T&&>(value);
    }

    template <typename T, typename U>
    constexpr auto exchange(T& value, U&& new_value) -> T {
        auto old_value = move(value);
        value = forward<U>(new_value);
        return old_value;
    }

    template <typename I, typename F>
    constexpr auto is_sorted(I first, I last, F&& comparison) -> bool {
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
    constexpr auto all_of(I first, I last, F&& predicate) -> bool {
        for (; first != last; ++first)
            if (!predicate(*first))
                return false;
        return true;
    }

    template <typename I, typename O>
    constexpr auto equal(I first, I last, O other) -> bool {
        for (; first != last; ++first, ++other)
            if (*first != *other)
                return false;
        return true;
    }

}

#endif
