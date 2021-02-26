#ifndef CPPLTF_ASSERT_HPP
#define CPPLTF_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

#define scope __func__

namespace test {

    inline auto check(bool value) noexcept -> bool {
        if (value) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename F>
    auto check(I first, I last, F&& predicate) noexcept -> bool {
        if (test::all_of(first, last, predicate)) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U, auto N>
    auto check(T (&array)[N], U&& predicate) noexcept -> bool {
        if (test::all_of(test::begin(array), test::end(array), predicate)) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) noexcept -> bool {
        if (left == right) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_equal(I first, I last, O other) noexcept -> bool {
        if (test::equal(first, last, other)) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U, auto N>
    auto check_equal(const T (&array)[N], const U (&other)[N]) noexcept -> bool {
        if (test::equal(test::begin(array), test::end(array), other)) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) noexcept -> bool {
        if (left != right) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_not_equal(I first, I last, O other) noexcept -> bool {
        if (!test::equal(first, last, other)) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U, auto N>
    auto check_not_equal(const T (&array)[N], const U (&other)[N]) noexcept -> bool {
        if (!test::equal(test::begin(array), test::end(array), other)) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) noexcept -> bool {
        if (left < right) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) noexcept -> bool {
        if (left >= right) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) noexcept -> bool {
        if (left > right) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) noexcept -> bool {
        if (left <= right) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename F, typename... V>
    auto check_throws(F&& function, V&&... args) noexcept -> bool {
        try {
            function(forward<V>(args)...);
            registry::on_error(scope);
            return false;
        } catch (...) {
            registry::on_success(scope);
            return true;
        }
    }

    template <typename F, typename... V>
    auto check_nothrows(F&& function, V&&... args) noexcept -> bool {
        try {
            function(forward<V>(args)...);
            registry::on_success(scope);
            return true;
        } catch (...) {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_sorted(I first, I last, O&& compare) noexcept -> bool {
        if (test::is_sorted(first, last, compare)) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U, auto N>
    auto check_sorted(const T (&array)[N], U&& compare) noexcept -> bool {
        if (test::is_sorted(test::begin(array), test::end(array), compare)) {
            registry::on_success(scope);
            return true;
        } else {
            registry::on_error(scope);
            return false;
        }
    }

}

#undef scope

#endif
