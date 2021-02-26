#include "common.hpp"

int main() {
    {
        test::unit("unit", [] { test::check(true); });
        test::unit("unit", [] { test::check_equal(0, 0); });
        CASSERT(test::code == test::exit_code::success);
    }
    {
        test::unit("unit", [] { test::check(false); });
        test::unit("unit", [] { test::check_equal(0, 0); });
        CASSERT(test::code == test::exit_code::failure);
    }
    {
        using namespace test;
        unit("this", [] {
            CASSERT(global.test_state.error_count == 0 && global.test_state.total_count == 0);
            unit("is", [] {
                CASSERT(global.test_state.error_count == 0 && global.test_state.total_count == 0);
                check(true);
                check(false);
            });
            unit("unreadable", [] {
                CASSERT(global.test_state.error_count == 0 && global.test_state.total_count == 0);
                check(true);
                check(false);
                unit("on", [] {
                    CASSERT(global.test_state.error_count == 1 && global.test_state.total_count == 2);
                    check(true);
                    check(false);
                    CASSERT(global.test_state.error_count == 2 && global.test_state.total_count == 4);
                });
                CASSERT(global.test_state.error_count == 1 && global.test_state.total_count == 2);
            });
            unit("purpose", [] {
                check(false);
                check(false);
                unit("do", [] {
                    check(true);
                    check(true);
                    CASSERT(global.test_state.error_count == 2 && global.test_state.total_count == 4);
                });
                CASSERT(global.test_state.error_count == 2 && global.test_state.total_count == 2);
                unit("not", [] {
                    check(true);
                    check(true);
                    CASSERT(global.test_state.error_count == 2 && global.test_state.total_count == 4);
                    unit("modify", [] {
                        check(true);
                        check(false);
                        CASSERT(global.test_state.error_count == 3 && global.test_state.total_count == 6);
                    });
                });
                CASSERT(global.test_state.error_count == 2 && global.test_state.total_count == 2);
            });
            CASSERT(global.test_state.error_count == 0 && global.test_state.total_count == 0);
        });
    }
}
