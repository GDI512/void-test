#ifndef VOID_TEST_ASSERT_HPP
#define VOID_TEST_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test {

    inline auto check(bool value) noexcept -> bool {
        if (value) {
            core::registry::on_success(__func__);
            return true;
        } else {
            core::registry::on_error(__func__);
            return false;
        }
    }

    template <typename callable, typename... args>
    auto check(callable&& function, args&&... arguments) noexcept -> bool {
        if (function(core::forward<args>(arguments)...)) {
            core::registry::on_success(__func__);
            return true;
        } else {
            core::registry::on_error(__func__);
            return false;
        }
    }

    template <typename type, typename other>
    auto check_equal(const type& left, const other& right) noexcept -> bool {
        if (left == right) {
            core::registry::on_success(__func__);
            return true;
        } else {
            core::registry::on_error(__func__);
            return false;
        }
    }

    template <typename type, typename other>
    auto check_not_equal(const type& left, const other& right) noexcept -> bool {
        if (left != right) {
            core::registry::on_success(__func__);
            return true;
        } else {
            core::registry::on_error(__func__);
            return false;
        }
    }

    template <typename type, typename other>
    auto check_less(const type& left, const other& right) noexcept -> bool {
        if (left < right) {
            core::registry::on_success(__func__);
            return true;
        } else {
            core::registry::on_error(__func__);
            return false;
        }
    }

    template <typename type, typename other>
    auto check_not_less(const type& left, const other& right) noexcept -> bool {
        if (left >= right) {
            core::registry::on_success(__func__);
            return true;
        } else {
            core::registry::on_error(__func__);
            return false;
        }
    }

    template <typename type, typename other>
    auto check_greater(const type& left, const other& right) noexcept -> bool {
        if (left > right) {
            core::registry::on_success(__func__);
            return true;
        } else {
            core::registry::on_error(__func__);
            return false;
        }
    }

    template <typename type, typename other>
    auto check_not_greater(const type& left, const other& right) noexcept -> bool {
        if (left <= right) {
            core::registry::on_success(__func__);
            return true;
        } else {
            core::registry::on_error(__func__);
            return false;
        }
    }

    template <typename callable, typename... args>
    auto check_throws(callable&& function, args&&... arguments) noexcept -> bool {
        try {
            function(core::forward<args>(arguments)...);
            core::registry::on_error(__func__);
            return false;
        } catch (...) {
            core::registry::on_success(__func__);
            return true;
        }
    }

    template <typename callable, typename... args>
    auto check_nothrows(callable&& function, args&&... arguments) noexcept -> bool {
        try {
            function(core::forward<args>(arguments)...);
            core::registry::on_success(__func__);
            return true;
        } catch (...) {
            core::registry::on_error(__func__);
            return false;
        }
    }

}

#endif
