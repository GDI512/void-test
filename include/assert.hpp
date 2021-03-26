#ifndef CPPLTF_ASSERT_HPP
#define CPPLTF_ASSERT_HPP

#include "state.hpp"
#include "output.hpp"
#include "utility.hpp"

#define scope __func__

namespace test {

    template <message select>
    auto action(string) noexcept -> bool = delete;

    template <>
    auto action<message::error>(string source) noexcept -> bool;

    template <>
    auto action<message::success>(string source) noexcept -> bool;

    template <>
    auto action<message::exception>(string source) noexcept -> bool;

    template <typename F>
    auto unit(string name, F function) noexcept {
        const auto context = registry(name);
        try {
            function();
        } catch (...) {
            action<message::exception>(name);
        }
        return 0;
    }

    inline auto check(bool value) {
        if (value) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename I, typename F>
    auto check(I first, I last, F predicate) {
        if (cpp::all_of(first, last, predicate)) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) {
        if (left == right) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename I, typename J>
    auto check_equal(I first, I last, J other) {
        if (cpp::equal(first, last, other)) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) {
        if (left != right) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename I, typename J>
    auto check_not_equal(I first, I last, J other) {
        if (!cpp::equal(first, last, other)) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) {
        if (left < right) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) {
        if (left >= right) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) {
        if (left > right) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) {
        if (left <= right) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename F, typename... V>
    auto check_throws(F&& function, V&&... arguments) {
        try {
            function(cpp::forward<V>(arguments)...);
            return action<message::error>(scope);
        } catch (...) {
            return action<message::success>(scope);
        }
    }

    template <typename F, typename... V>
    auto check_nothrows(F&& function, V&&... arguments) {
        try {
            function(cpp::forward<V>(arguments)...);
            return action<message::success>(scope);
        } catch (...) {
            return action<message::error>(scope);
        }
    }

    template <typename I, typename F>
    auto check_sorted(I first, I last, F compare) {
        if (cpp::is_sorted(first, last, compare)) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

    template <typename I, typename T>
    auto check_contains(I first, I last, const T& value) {
        if (cpp::find(first, last, value) != last) {
            return action<message::success>(scope);
        } else {
            return action<message::error>(scope);
        }
    }

}

#undef scope

#endif
