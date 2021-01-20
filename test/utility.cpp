// ============================================================================
//  Test file for utility functions and classes
//      1. Check if remove_reference really removes references
//      2. Check if is_value_reference detects lvalue references
//      3. Ensure forward does proper type casting
//      3. Test the atomic counter class
// ============================================================================

// clang-format off

#include "common.hpp"

#include <utility>
#include <type_traits>

using namespace void_test::core;

int main() {
    { // 1.
        static_assert(std::is_same_v<int, remove_reference<int>::type>);
        static_assert(std::is_same_v<int, remove_reference<int&>::type>);
        static_assert(std::is_same_v<int, remove_reference<int&&>::type>);
    }
    { // 2.
        static_assert(is_lvalue_reference<int&>::value);
        static_assert(!is_lvalue_reference<int>::value);
        static_assert(!is_lvalue_reference<int&&>::value);
    }
    { // 3.
        auto value = 4;
        auto rvalue = [](int x) -> int { return x; };
        auto lvalue = [](int& x) -> int& { return x; };
        static_assert(std::is_same_v<int&&, decltype(std::forward<int>(lvalue(value)))>);
        static_assert(std::is_same_v<int&&, decltype(std::forward<int>(rvalue(value)))>);
    }
    { // 4.
        auto counter = atomic_counter();
        cassert(counter++ == 0);
        cassert(counter++ == 1);
        cassert(counter++ == 2);
        cassert(counter-- == 3);
        cassert(counter-- == 2);
        cassert(counter-- == 1);
        cassert(counter == 0);
    }
}
