// ============================================================================
//  Test file for all of the functionality exposed in the API combined
//      1. Create the first test
//      2. Check if test is considered successful by default
//      3. Test all assertions which should pass inside a unit
//      4. Check if test is still considered to be passing
//      5. Test all assertions which should fail
//      6. Check if it changes the state of the test
//      7. Create another global-variable-test thing
//      8. Create a unit containing a good example of resource management
//      9. Ensure it doesn't cause the test to fail
//     10. Do the same thing but simulate a double-destroy error
//     11. Ensure it causes the test to fail
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

// clang-format off

namespace test = void_test;

auto assertions = test::unit("main", []() { // 1.

    assert(test::core::global::exit_status() == test::core::exit_success); // 2.

    test::unit("good-values", [](){ // 3.
        assert(test::check(true));
        assert(test::check_equal(2, 2));
        assert(test::check_not_equal(2, 4));
        assert(test::check_greater(8, 4));
        assert(test::check_not_greater(4, 4));
        assert(test::check_not_greater(2, 4));
        assert(test::check_less(2, 4));
        assert(test::check_not_less(4, 4));
        assert(test::check_not_less(8, 4));
        assert(test::check_throws([](){ throw 0; }));
        assert(test::check_nothrows([](){ return 0; }));
    });

    assert(test::core::global::exit_status() == test::core::exit_success); // 4.

    test::unit("bad-values", [](){ // 5.
        assert(!test::check(false));
        assert(!test::check_equal(1, 2));
        assert(!test::check_not_equal(2, 2));
        assert(!test::check_greater(2, 4));
        assert(!test::check_greater(4, 4));
        assert(!test::check_not_greater(8, 4));
        assert(!test::check_less(8, 4));
        assert(!test::check_less(4, 4));
        assert(!test::check_not_less(2, 4));
        assert(!test::check_throws([](){ return 0; }));
        assert(!test::check_nothrows([](){ throw 0; }));
    });

    assert(test::core::global::exit_status() == test::core::exit_failure); // 6.

    test::core::global::exit_status(test::core::exit_success);

});

auto types = test::unit("main", [](){ // 7.

    assert(test::core::global::exit_status() == test::core::exit_success);

    test::unit("resource-no-error", [](){ // 8.
        test::resource automatic[64] = {};
        auto* dynamic = new test::resource[64];
        delete[] dynamic;
    });

    assert(test::core::global::exit_status() == test::core::exit_success); // 9.

    test::unit("resource-error", [](){ // 10.
        test::resource automatic[64] = {};
        for (auto& item : automatic) {
            item.~resource();
        }
    });

    assert(test::core::global::exit_status() == test::core::exit_failure); // 11.

    test::core::global::exit_status(test::core::exit_success);

});

// clang-format on
