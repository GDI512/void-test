#include <void_test.hpp>
#include "common.hpp"

// clang-format off

int main() {

test::unit("main unit", [](){

    test::unit("unit with passing assertions", [](){

        CHECK(test::assert(true));
        CHECK(test::assert([](){ return true; }));  // We just check if all assertions
        CHECK(test::assert_equal(1, 1));            // with arguments that would make them pass
        CHECK(test::assert_less(1, 2));             // actually make them pass
        CHECK(test::assert_not_less(2, 2));
        CHECK(test::assert_not_less(4, 2));
        CHECK(test::assert_greater(2, 1));
        CHECK(test::assert_not_greater(2, 2));
        CHECK(test::assert_not_greater(2, 4));
        CHECK(test::assert_throws([](){ throw 0; }));
        CHECK(test::assert_nothrows([](){ return 0; }));

    });

    CHECK(test::exit_status() == test::exit_success);   // All assertions passed

    test::unit("unit with failing assertions", [](){

        CHECK(!test::assert(false));                    // Here we do the inverse
        CHECK(!test::assert([](){ return false; }));    // of what we did in the unit above
        CHECK(!test::assert_equal(1, 2));
        CHECK(!test::assert_less(2, 1));
        CHECK(!test::assert_less(2, 2));
        CHECK(!test::assert_not_less(2, 4));
        CHECK(!test::assert_greater(1, 2));
        CHECK(!test::assert_greater(2, 2));
        CHECK(!test::assert_not_greater(4, 2));
        CHECK(!test::assert_throws([](){ return 0; }));
        CHECK(!test::assert_nothrows([](){ throw 0; }));

    });

    CHECK(test::exit_status() == test::exit_failure);   // Previous assertions failed

});

}

// clang-format on
