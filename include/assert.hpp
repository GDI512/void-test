#ifndef VOID_TEST_ASSERT_HPP
#define VOID_TEST_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test {

    inline auto check(bool value) noexcept -> bool {
        if (value) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename... U>
    auto check(T&& function, U&&... args) noexcept -> bool {
        if (function(core::forward<U>(args)...)) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) noexcept -> bool {
        if (left == right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename U>
    auto check_equal(T first, T last, U other) noexcept -> bool {
        for (; first != last; ++first, ++other) {
            if (*first != *other) {
                return core::on_error(__func__);
            }
        }
        return core::on_success(__func__);
    }

    template <typename T, typename U, auto N>
    auto check_equal(const T (&array)[N], const U (&other)[N]) noexcept -> bool {
        for (auto i = 0; i < N; i++) {
            if (array[i] != other[i]) {
                return core::on_error(__func__);
            }
        }
        return core::on_success(__func__);
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) noexcept -> bool {
        if (left != right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename U>
    auto check_not_equal(T first, T last, U other) noexcept -> bool {
        for (; first != last; ++first, ++other) {
            if (*first != *other) {
                return core::on_success(__func__);
            }
        }
        return core::on_error(__func__);
    }

    template <typename T, typename U, auto N>
    auto check_not_equal(const T (&array)[N], const U (&other)[N]) noexcept -> bool {
        for (auto i = 0; i < N; i++) {
            if (array[i] != other[i]) {
                return core::on_success(__func__);
            }
        }
        return core::on_error(__func__);
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) noexcept -> bool {
        if (left < right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) noexcept -> bool {
        if (left >= right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) noexcept -> bool {
        if (left > right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) noexcept -> bool {
        if (left <= right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename... U>
    auto check_throws(T&& function, U&&... args) noexcept -> bool {
        try {
            function(core::forward<U>(args)...);
            return core::on_error(__func__);
        } catch (...) {
            return core::on_success(__func__);
        }
    }

    template <typename T, typename... U>
    auto check_nothrows(T&& function, U&&... args) noexcept -> bool {
        try {
            function(core::forward<U>(args)...);
            return core::on_success(__func__);
        } catch (...) {
            return core::on_error(__func__);
        }
    }

    template <typename T, typename U>
    auto check_sorted(const T& container, U compare) noexcept -> bool {
        auto first = core::begin(container);
        const auto last = core::end(container);
        if (first == last) {
            return core::on_success(__func__);
        }
        auto next = ++core::begin(container);
        if (next == last) {
            return core::on_success(__func__);
        }
        for (; next != last; ++first, ++next) {
            if (!compare(*first, *next)) {
                return core::on_error(__func__);
            }
        }
        return core::on_success(__func__);
    }

    template <typename T, typename U, auto N>
    auto check_sorted(const T (&array)[N], U compare) noexcept -> bool {
        auto first = core::begin(array);
        const auto last = core::end(array);
        if (N <= 1) {
            return core::on_success(__func__);
        }
        for (; first != last - 1; ++first) {
            if (!compare(*first, *(first + 1))) {
                return core::on_error(__func__);
            }
        }
        return core::on_success(__func__);
    }

}

#endif
