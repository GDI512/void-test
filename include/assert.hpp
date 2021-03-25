#ifndef CPPLTF_ASSERT_HPP
#define CPPLTF_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

#define scope __func__

namespace test {

    template <typename F>
    auto unit(string name, F function) noexcept {
        const auto context = registry(name);
        try {
            function();
        } catch (...) {
            on_exception();
        }
        return 0;
    }

    inline auto check(bool value) {
        if (value) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename I, typename F>
    auto check(I first, I last, F predicate) {
        if (cpp::all_of(first, last, predicate)) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) {
        if (left == right) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename I, typename J>
    auto check_equal(I first, I last, J other) {
        if (cpp::equal(first, last, other)) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) {
        if (left != right) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename I, typename J>
    auto check_not_equal(I first, I last, J other) {
        if (!cpp::equal(first, last, other)) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) {
        if (left < right) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) {
        if (left >= right) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) {
        if (left > right) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) {
        if (left <= right) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename F, typename... V>
    auto check_throws(F&& function, V&&... arguments) {
        try {
            function(cpp::forward<V>(arguments)...);
            return on_error(scope);
        } catch (...) {
            return on_success(scope);
        }
    }

    template <typename F, typename... V>
    auto check_nothrows(F&& function, V&&... arguments) {
        try {
            function(cpp::forward<V>(arguments)...);
            return on_success(scope);
        } catch (...) {
            return on_error(scope);
        }
    }

    template <typename I, typename F>
    auto check_sorted(I first, I last, F compare) {
        if (cpp::is_sorted(first, last, compare)) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

    template <typename I, typename T>
    auto check_contains(I first, I last, const T& value) {
        if (cpp::find(first, last, value) != last) {
            return on_success(scope);
        } else {
            return on_error(scope);
        }
    }

}

#undef scope

#endif
