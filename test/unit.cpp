// ============================================================================
//  Test file for utilities used for grouping assertions / test cases.
//      1. Ensure calling an empty unit returns true and does not change the
//         global test state
//      2. Ensure calling a unit with a passing assertion returns true and does
//         not change the global test state
//      3. Ensure calling a unit with a failing assertion returns false and
//         fails the test
//      4. Ensure unit gets its name set properly
//      5. Ensure the expected behavior of nested units with passing and
//         failing assertions
// ============================================================================

#include "common.hpp"

using namespace test;
using namespace test::core;

int main() {
    { // 1.
        cassert(unit("unit-name", []() {}) == true);
        cassert(global::exit_status() == exit_success);
    }
    { // 2.
        cassert(unit("unit-name", []() { check(true); }) == true);
        cassert(global::exit_status() == exit_success);
    }
    { // 3.
        cassert(unit("unit-name", []() { check(false); }) == false);
        cassert(global::exit_status() == exit_failure);
    }
    { // 4.
        unit("unit-name", []() { cassert(cmpstr(scope::data(), "unit-name") == 0); });
    }
    { // 5.
        global::exit_status(exit_success);
        auto test = unit("unit-main", []() {
            cassert(unit("unit-one", []() {
                check_equal(0, 0);
                check_not_equal(0, 1);
            }));
            cassert(!unit("unit-two", []() {
                check_equal(0, 1);
                check_not_equal(0, 0);
            }));
        });
        cassert(test);
        cassert(global::exit_status() == exit_failure);
        static_cast<void>(test);
    }
}
