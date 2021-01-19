// ============================================================================
//  Test file for basic assertion functions.
//      1. Tests the bool expression assertion
//      2. Test the function-returning-bool assertion
//      3. Test the equality assertion
//      4. Test the inequality assertion
//      5. Test the less-than assertion
//      6. Test the not-less-than assertion
//      7. Test the greater-than assertion
//      8. Test the not-greater-than
//      9. Test the throw assertion
//     10. Test the nothrow assertion
// ============================================================================

#include "common.hpp"

#define cassert(x)                                                                                                     \
    if (!(x)) {                                                                                                        \
        print(__LINE__, #x);                                                                                           \
        stop(1);                                                                                                       \
    }

using namespace void_test;
using namespace void_test::core;

int main() {
    { // 1.
        registry state;
        cassert(check(true));
        cassert(!check(false));
    }
    { // 2.
        registry state;
        cassert(check([](auto x) { return x; }, true));
        cassert(!check([](auto x) { return x; }, false));
    }
    { // 3.
        registry state;
        cassert(check_equal(2, 2));
        cassert(!check_equal(2, 4));
    }
    { // 4.
        registry state;
        cassert(check_not_equal(2, 4));
        cassert(!check_not_equal(2, 2));
    }
    { // 5.
        registry state;
        cassert(check_less(2, 4));
        cassert(!check_less(2, 2));
        cassert(!check_less(2, 1));
    }
    { // 6.
        registry state;
        cassert(check_not_less(2, 2));
        cassert(check_not_less(4, 2));
        cassert(!check_not_less(1, 2));
    }
    { // 7.
        registry state;
        cassert(check_greater(4, 2));
        cassert(!check_greater(2, 2));
        cassert(!check_greater(1, 2));
    }
    { // 8.
        registry state;
        cassert(check_not_greater(2, 2));
        cassert(check_not_greater(2, 4));
        cassert(!check_not_greater(2, 1));
    }
    { // 9.
        registry state;
        cassert(check_throws([]() { throw 0; }));
        cassert(!check_throws([]() { return 0; }));
    }
    { // 10.
        registry state;
        cassert(check_nothrows([]() { return 0; }));
        cassert(!check_nothrows([]() { throw 0; }));
    }
}
