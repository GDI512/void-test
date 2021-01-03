// ============================================================================
//  Content:
//      Test file for basic assertion functions.
//  Tests:
//      1. Check the bool value assertion
//      2. Check the assertion for functions with bool-convertible return values
//      3. Check the equality assertion
//      4. Check the inequality assertion
//      5. Check the less-than assertion
//      6. Check the not-less-than assertion
//      7. Check the greater-than assertion
//      8. Check the not-greater-than assertion
//      9. Check the throw assertion
//     10. Check the nothrow assertion
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
