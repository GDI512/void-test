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
    auto check_not_equal(const T& left, const U& right) noexcept -> bool {
        if (left != right) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
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

}

#endif
