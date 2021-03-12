#ifndef CPPLTF_ASSERT_HPP
#define CPPLTF_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test {

    inline auto check(bool value) -> bool {
        if (value) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename input, typename invocable>
    auto check(input first, input last, invocable predicate) -> bool {
        if (core::all_of(first, last, predicate)) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename value_type, typename other_type>
    auto check_equal(const value_type& left, const other_type& right) -> bool {
        if (left == right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename input, typename other>
    auto check_equal(input first, input last, other ofirst) -> bool {
        if (core::equal(first, last, ofirst)) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename value_type, typename other_type>
    auto check_not_equal(const value_type& left, const other_type& right) -> bool {
        if (left != right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename input, typename other>
    auto check_not_equal(input first, input last, other ofirst) -> bool {
        if (!core::equal(first, last, ofirst)) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename value_type, typename other_type>
    auto check_less(const value_type& left, const other_type& right) -> bool {
        if (left < right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename value_type, typename other_type>
    auto check_not_less(const value_type& left, const other_type& right) -> bool {
        if (left >= right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename value_type, typename other_type>
    auto check_greater(const value_type& left, const other_type& right) -> bool {
        if (left > right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename value_type, typename other_type>
    auto check_not_greater(const value_type& left, const other_type& right) -> bool {
        if (left <= right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename invocable, typename... args>
    auto check_throws(invocable&& function, args&&... arguments) -> bool {
        try {
            function(core::forward<args>(arguments)...);
            return core::on_error(__func__);
        } catch (...) {
            return core::on_success(__func__);
        }
    }

    template <typename invocable, typename... args>
    auto check_nothrows(invocable&& function, args&&... arguments) -> bool {
        try {
            function(core::forward<args>(arguments)...);
            return core::on_success(__func__);
        } catch (...) {
            return core::on_error(__func__);
        }
    }

    template <typename input, typename invocable>
    auto check_sorted(input first, input last, invocable compare) -> bool {
        if (core::is_sorted(first, last, compare)) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename input, typename value_type>
    auto check_contains(input first, input last, const value_type& value) -> bool {
        if (core::find(first, last, value) != last) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

}

#endif
