#ifndef CITRINE_ASSERT_HPP
#define CITRINE_ASSERT_HPP

#include "utility.hpp"
#include "state.hpp"

namespace test {

    template <auto N>
    auto handle(string) noexcept -> bool;

    template <>
    auto handle<message::error>(string source) noexcept -> bool;

    template <>
    auto handle<message::success>(string source) noexcept -> bool;

    template <typename F>
    auto unit(string name, F function) noexcept {
        const auto context = registry(name);
        try {
            function();
        } catch (...) {
            report<message::exception>();
        }
        return 0;
    }

    inline auto check(bool value) noexcept {
        if (value)
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename T, typename F>
    auto check(T first, T last, F predicate) {
        if (test::all_of(first, last, predicate))
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) {
        if (left == right)
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename I, typename J>
    auto check_equal(I first, I last, J start) {
        if (test::equal(first, last, start))
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) {
        if (left != right)
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename T, typename J>
    auto check_not_equal(T first, T last, J start) {
        if (!test::equal(first, last, start))
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) {
        if (left < right)
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) {
        if (left >= right)
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) {
        if (left > right)
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) {
        if (left <= right)
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename F, typename... V>
    auto check_throws(F function, V&&... arguments) {
        try {
            function(test::forward<V>(arguments)...);
            return handle<message::error>(__func__);
        } catch (...) {
            return handle<message::success>(__func__);
        }
    }

    template <typename F, typename... V>
    auto check_nothrows(F function, V&&... arguments) {
        try {
            function(test::forward<V>(arguments)...);
            return handle<message::success>(__func__);
        } catch (...) {
            return handle<message::error>(__func__);
        }
    }

    template <typename T, typename F>
    auto check_sorted(T first, T last, F compare) {
        if (test::is_sorted(first, last, compare))
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

    template <typename I, typename T>
    auto check_contains(I first, I last, const T& value) {
        if (test::find(first, last, value) != last)
            return handle<message::success>(__func__);
        else
            return handle<message::error>(__func__);
    }

}

#endif
