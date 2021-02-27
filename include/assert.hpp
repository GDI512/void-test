#ifndef CPPLTF_ASSERT_HPP
#define CPPLTF_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

#define scope __func__

namespace test {

    inline auto check(bool value) -> bool {
        if (value) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename F>
    auto check(I first, I last, F&& predicate) -> bool {
        if (aux::all_of(first, last, predicate)) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) -> bool {
        if (left == right) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_equal(I first, I last, O other) -> bool {
        if (aux::equal(first, last, other)) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) -> bool {
        if (left != right) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_not_equal(I first, I last, O other) -> bool {
        if (!aux::equal(first, last, other)) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) -> bool {
        if (left < right) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) -> bool {
        if (left >= right) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) -> bool {
        if (left > right) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) -> bool {
        if (left <= right) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename F, typename... V>
    auto check_throws(F&& function, V&&... args) -> bool {
        try {
            function(aux::forward<V>(args)...);
            aux::registry::on_error(scope);
            return false;
        } catch (...) {
            aux::registry::on_success(scope);
            return true;
        }
    }

    template <typename F, typename... V>
    auto check_nothrows(F&& function, V&&... args) -> bool {
        try {
            function(aux::forward<V>(args)...);
            aux::registry::on_success(scope);
            return true;
        } catch (...) {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename O>
    auto check_sorted(I first, I last, O&& compare) -> bool {
        if (aux::is_sorted(first, last, compare)) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

    template <typename I, typename T>
    auto check_contains(I first, I last, const T& value) -> bool {
        if (aux::find(first, last, value) != last) {
            aux::registry::on_success(scope);
            return true;
        } else {
            aux::registry::on_error(scope);
            return false;
        }
    }

}

#undef scope

#endif
