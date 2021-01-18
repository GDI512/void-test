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

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

using void_test::core::registry;
using namespace void_test;

int main() {
    { // 1.
        registry state;
        assert(check(true));
        assert(!check(false));
    }
    { // 2.
        registry state;
        assert(check([](auto x) { return x; }, true));
        assert(!check([](auto x) { return x; }, false));
    }
    { // 3.
        registry state;
        assert(check_equal(2, 2));
        assert(!check_equal(2, 4));
    }
    { // 4.
        registry state;
        assert(check_not_equal(2, 4));
        assert(!check_not_equal(2, 2));
    }
    { // 5.
        registry state;
        assert(check_less(2, 4));
        assert(!check_less(2, 2));
        assert(!check_less(2, 1));
    }
    { // 6.
        registry state;
        assert(check_not_less(2, 2));
        assert(check_not_less(4, 2));
        assert(!check_not_less(1, 2));
    }
    { // 7.
        registry state;
        assert(check_greater(4, 2));
        assert(!check_greater(2, 2));
        assert(!check_greater(1, 2));
    }
    { // 8.
        registry state;
        assert(check_not_greater(2, 2));
        assert(check_not_greater(2, 4));
        assert(!check_not_greater(2, 1));
    }
    { // 9.
        registry state;
        assert(check_throws([]() { throw 0; })); // NOLINT
        assert(!check_throws([]() { return 0; }));
    }
    { // 10.
        registry state;
        assert(check_nothrows([]() { return 0; }));
        assert(!check_nothrows([]() { throw 0; })); // NOLINT
    }
}
