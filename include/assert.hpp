#ifndef VOIDTEST_ASSERT_HPP
#define VOIDTEST_ASSERT_HPP

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

    template <typename fn, typename... args>
    auto check(fn&& function, args&&... arguments) noexcept -> bool {
        if (function(core::forward<args>(arguments)...)) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename type, typename other>
    auto check_equal(const type& left, const other& right) noexcept -> bool {
        if (left == right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename type, typename other>
    auto check_not_equal(const type& left, const other& right) noexcept -> bool {
        if (left != right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename type, typename other>
    auto check_less(const type& left, const other& right) noexcept -> bool {
        if (left < right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename type, typename other>
    auto check_not_less(const type& left, const other& right) noexcept -> bool {
        if (left >= right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename type, typename other>
    auto check_greater(const type& left, const other& right) noexcept -> bool {
        if (left > right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename type, typename other>
    auto check_not_greater(const type& left, const other& right) noexcept -> bool {
        if (left <= right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

    template <typename fn, typename... args>
    auto check_throws(fn&& function, args&&... arguments) noexcept -> bool {
        try {
            function(core::forward<args>(arguments)...);
            return core::on_error(__func__);
        } catch (...) {
            return core::on_success(__func__);
        }
    }

    template <typename fn, typename... args>
    auto check_nothrows(fn&& function, args&&... arguments) noexcept -> bool {
        try {
            function(core::forward<args>(arguments)...);
            return core::on_success(__func__);
        } catch (...) {
            return core::on_error(__func__);
        }
    }

}

#endif
