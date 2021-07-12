#ifndef CITRINE_ASSERT_HPP
#define CITRINE_ASSERT_HPP

#include "utility.hpp"
#include "state.hpp"

namespace citrine {

    template <typename invocable>
    auto unit(string name, invocable function) noexcept {
        auto state = unit_state(name);
        try {
            function();
        } catch (...) {
            state.on_exception();
        }
        return 0;
    }

    inline auto check(bool value) noexcept {
        if (value)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename iterator, typename invocable>
    auto check(iterator first, iterator last, invocable predicate) {
        if (citrine::all_of(first, last, predicate))
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename value_type, typename other_type>
    auto check_equal(const value_type& left, const other_type& right) {
        if (left == right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename iterator, typename other_iterator>
    auto check_equal(iterator first, iterator last, other_iterator start) {
        if (citrine::equal(first, last, start))
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename value_type, typename other_type>
    auto check_not_equal(const value_type& left, const other_type& right) {
        if (left != right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename iterator, typename J>
    auto check_not_equal(iterator first, iterator last, J start) {
        if (!citrine::equal(first, last, start))
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename value_type, typename other_type>
    auto check_less(const value_type& left, const other_type& right) {
        if (left < right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename value_type, typename other_type>
    auto check_not_less(const value_type& left, const other_type& right) {
        if (left >= right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename value_type, typename other_type>
    auto check_greater(const value_type& left, const other_type& right) {
        if (left > right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename value_type, typename other_type>
    auto check_not_greater(const value_type& left, const other_type& right) {
        if (left <= right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename invocable, typename... args>
    auto check_throws(invocable function, args&&... arguments) {
        try {
            function(citrine::forward<args>(arguments)...);
            return unit_state::active().on_error(__func__);
        } catch (...) {
            return unit_state::active().on_success(__func__);
        }
    }

    template <typename invocable, typename... args>
    auto check_nothrows(invocable function, args&&... arguments) {
        try {
            function(citrine::forward<args>(arguments)...);
            return unit_state::active().on_success(__func__);
        } catch (...) {
            return unit_state::active().on_error(__func__);
        }
    }

    template <typename iterator, typename invocable>
    auto check_sorted(iterator first, iterator last, invocable compare) {
        if (citrine::is_sorted(first, last, compare))
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename iterator, typename value_type>
    auto check_contains(iterator first, iterator last, const value_type& value) {
        if (citrine::find(first, last, value) != last)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

}

#endif
