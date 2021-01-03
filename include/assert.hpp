#ifndef VOID_TEST_CHECK_HPP
#define VOID_TEST_CHECK_HPP

#include "output.hpp"
#include "utility.hpp"
#include "registry.hpp"

namespace void_test {

    inline auto check(bool value) noexcept -> bool {
        if (value) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename F, typename... A>
    auto check(F&& function, A&&... arguments) noexcept -> bool {
        if (function(core::forward<A>(arguments)...)) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) noexcept -> bool {
        if (left == right) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) noexcept -> bool {
        if (left != right) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) noexcept -> bool {
        if (left < right) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) noexcept -> bool {
        if (left >= right) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) noexcept -> bool {
        if (left > right) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) noexcept -> bool {
        if (left <= right) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename F, typename... A>
    auto check_throws(F&& function, A&&... arguments) noexcept -> bool {
        try {
            function(core::forward<A>(arguments)...);
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        } catch (...) {
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        }
    }

    template <typename F, typename... A>
    auto check_nothrows(F&& function, A&&... arguments) noexcept -> bool {
        try {
            function(core::forward<A>(arguments)...);
            core::registry::on_success();
            core::output::on_success(__func__);
            return true;
        } catch (...) {
            core::registry::on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

}

#endif
