#ifndef VOID_TEST_ASSERT_HPP
#define VOID_TEST_ASSERT_HPP

#include "output.hpp"
#include "utility.hpp"

namespace test {

    inline auto assert(bool value) noexcept -> bool {
        if (value) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename F, typename... A>
    auto assert(F&& function, A&&... arguments) noexcept -> bool {
        if (function(core::forward(arguments)...)) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto assert_equal(const T& left, const U& right) noexcept -> bool {
        if (left == right) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto assert_not_equal(const T& left, const U& right) noexcept -> bool {
        if (left != right) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto assert_less(const T& left, const U& right) noexcept -> bool {
        if (left < right) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto assert_not_less(const T& left, const U& right) noexcept -> bool {
        if (left >= right) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto assert_greater(const T& left, const U& right) noexcept -> bool {
        if (left > right) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename T, typename U>
    auto assert_not_greater(const T& left, const U& right) noexcept -> bool {
        if (left <= right) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } else {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

    template <typename F, typename... A>
    auto assert_throws(F&& function, A&&... arguments) noexcept -> bool {
        try {
            function(core::forward(arguments)...);
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        } catch (...) {
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        }
    }

    template <typename F, typename... A>
    auto assert_nothrows(F&& function, A&&... arguments) noexcept -> bool {
        try {
            function(core::forward(arguments)...);
            core::test_registry::current().on_success();
            core::output::on_success(__func__);
            return true;
        } catch (...) {
            core::test_registry::current().on_error();
            core::output::on_error(__func__);
            return false;
        }
    }

}

#endif
