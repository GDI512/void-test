#ifndef CPPLTF_ASSERT_HPP
#define CPPLTF_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

#define func __func__

namespace test {

    inline auto check(bool value) -> bool {
        if (value) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename I, typename F>
    auto check(I first, I last, F&& predicate) -> bool {
        if (core::all_of(first, last, predicate)) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) -> bool {
        if (left == right) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_equal(I first, I last, O other) -> bool {
        if (core::equal(first, last, other)) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) -> bool {
        if (left != right) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_not_equal(I first, I last, O other) -> bool {
        if (!core::equal(first, last, other)) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) -> bool {
        if (left < right) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) -> bool {
        if (left >= right) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) -> bool {
        if (left > right) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) -> bool {
        if (left <= right) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename F, typename... V>
    auto check_throws(F&& function, V&&... args) -> bool {
        try {
            function(core::forward<V>(args)...);
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        } catch (...) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        }
    }

    template <typename F, typename... V>
    auto check_nothrows(F&& function, V&&... args) -> bool {
        try {
            function(core::forward<V>(args)...);
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } catch (...) {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_sorted(I first, I last, O&& compare) -> bool {
        if (core::is_sorted(first, last, compare)) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

    template <typename I, typename T>
    auto check_contains(I first, I last, const T& value) -> bool {
        if (core::find(first, last, value) != last) {
            core::registry::on_success();
            core::output::on_success(func);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(func);
            return false;
        }
    }

}

#undef func

#endif
