#ifndef CITRINE_ASSERT_HPP
#define CITRINE_ASSERT_HPP

#include "utility.hpp"
#include "state.hpp"

namespace citrine {

    template <typename F>
    auto unit(string name, F function) noexcept {
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

    template <typename T, typename F>
    auto check(T first, T last, F predicate) {
        if (citrine::all_of(first, last, predicate))
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) {
        if (left == right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename I, typename J>
    auto check_equal(I first, I last, J start) {
        if (citrine::equal(first, last, start))
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) {
        if (left != right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename T, typename J>
    auto check_not_equal(T first, T last, J start) {
        if (!citrine::equal(first, last, start))
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) {
        if (left < right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) {
        if (left >= right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) {
        if (left > right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) {
        if (left <= right)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename F, typename... V>
    auto check_throws(F function, V&&... arguments) {
        try {
            function(citrine::forward<V>(arguments)...);
            return unit_state::active().on_error(__func__);
        } catch (...) {
            return unit_state::active().on_success(__func__);
        }
    }

    template <typename F, typename... V>
    auto check_nothrows(F function, V&&... arguments) {
        try {
            function(citrine::forward<V>(arguments)...);
            return unit_state::active().on_success(__func__);
        } catch (...) {
            return unit_state::active().on_error(__func__);
        }
    }

    template <typename T, typename F>
    auto check_sorted(T first, T last, F compare) {
        if (citrine::is_sorted(first, last, compare))
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

    template <typename I, typename T>
    auto check_contains(I first, I last, const T& value) {
        if (citrine::find(first, last, value) != last)
            return unit_state::active().on_success(__func__);
        else
            return unit_state::active().on_error(__func__);
    }

}

#endif
