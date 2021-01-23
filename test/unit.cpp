#include "common.hpp"

using namespace test;

int main() {
    {
        unit("unit", [] { check(true); });
        unit("unit", [] { check_equal(0, 0); });
        cassert(core::exit_code() == core::exit_success);
    }
    {
        unit("unit", [] { check(false); });
        unit("unit", [] { check_equal(0, 0); });
        cassert(core::exit_code() == core::exit_failure);
    }
    { // clang-format off
        using namespace test::core;
        unit("this", [] { cassert(global_test_state.error_count == 0 && global_test_state.total_count == 0);
            unit("is", [] { cassert(global_test_state.error_count == 0 && global_test_state.total_count == 0);
                check(true);
                check(false);
            });
            unit("unreadable", [] { cassert(global_test_state.error_count == 0 && global_test_state.total_count == 0);
                check(true);
                check(false);
                unit("on", [] { cassert(global_test_state.error_count == 1 && global_test_state.total_count == 2);
                    check(true);
                    check(false);
                    cassert(global_test_state.error_count == 2 && global_test_state.total_count == 4);
                });
                cassert(global_test_state.error_count == 1 && global_test_state.total_count == 2);
            });
            unit("purpose", [] {
                check(false);
                check(false);
                unit("do", [] {
                    check(true);
                    check(true);
                    cassert(global_test_state.error_count == 2 && global_test_state.total_count == 4);
                });
                cassert(global_test_state.error_count == 2 && global_test_state.total_count == 2);
                unit("not", [] {
                    check(true);
                    check(true);
                    cassert(global_test_state.error_count == 2 && global_test_state.total_count == 4);
                    unit("modify", [] {
                        check(true);
                        check(false);
                        cassert(global_test_state.error_count == 3 && global_test_state.total_count == 6);
                    });
                });
                cassert(global_test_state.error_count == 2 && global_test_state.total_count == 2);
            });
            cassert(global_test_state.error_count == 0 && global_test_state.total_count == 0);
        });
    } // clang-format on
}
