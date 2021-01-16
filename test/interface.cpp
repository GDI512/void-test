// ============================================================================
//  Test file for all of the functionality exposed in the API combined
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

// clang-format off

namespace test = void_test;

auto assertions = test::group([]() {

    assert(test::core::global::exit_status() == test::core::exit_success);

    test::unit("good-values", [](){
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

    assert(test::core::global::exit_status() == test::core::exit_success);

    test::unit("bad-values", [](){
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

    assert(test::core::global::exit_status() == test::core::exit_failure);

    test::core::global::exit_status(test::core::exit_success);

});

auto types = test::group([](){

    assert(test::core::global::exit_status() == test::core::exit_success);

    test::unit("resource-no-error", [](){
        test::resource automatic[64] = {};
        auto* dynamic = new test::resource[64];
        delete[] dynamic;
    });

    assert(test::core::global::exit_status() == test::core::exit_success);

    test::unit("resource-error", [](){
        test::resource automatic[64] = {};
        for (auto& item : automatic) {
            item.~resource();
        }
    });

    assert(test::core::global::exit_status() == test::core::exit_failure);

    test::core::global::exit_status(test::core::exit_success);

});

// clang-format on
