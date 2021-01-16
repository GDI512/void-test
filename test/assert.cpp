// ============================================================================
//  Test file for basic assertion functions.
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

using void_test::core::registry;
using namespace void_test;

int main() {
    {
        registry state;
        assert(check(true));
        assert(!check(false));
    }
    {
        registry state;
        assert(check([](auto x) { return x; }, true));
        assert(!check([](auto x) { return x; }, false));
    }
    {
        registry state;
        assert(check_equal(2, 2));
        assert(!check_equal(2, 4));
    }
    {
        registry state;
        assert(check_not_equal(2, 4));
        assert(!check_not_equal(2, 2));
    }
    {
        registry state;
        assert(check_less(2, 4));
        assert(!check_less(2, 2));
        assert(!check_less(2, 1));
    }
    {
        registry state;
        assert(check_not_less(2, 2));
        assert(check_not_less(4, 2));
        assert(!check_not_less(1, 2));
    }
    {
        registry state;
        assert(check_greater(4, 2));
        assert(!check_greater(2, 2));
        assert(!check_greater(1, 2));
    }
    {
        registry state;
        assert(check_not_greater(2, 2));
        assert(check_not_greater(2, 4));
        assert(!check_not_greater(2, 1));
    }
    {
        registry state;
        assert(check_throws([]() { throw 0; })); // NOLINT
        assert(!check_throws([]() { return 0; }));
    }
    {
        registry state;
        assert(check_nothrows([]() { return 0; }));
        assert(!check_nothrows([]() { throw 0; })); // NOLINT
    }
}
