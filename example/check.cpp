// ================================================================
//    This file contains examples of all available assertions.
//  In <cppltf> every assertion is defined as a function returning
//  true on success and false on failure.
// ================================================================

#include <cppltf.hpp>

const auto unit = test::unit("assertions", []{

    // ================================================
    //  The test::check assertion has overloads for
    //  pure bool expressions or ranges delimited by
    //  iterators.
    // ================================================

    test::unit("test::check", []{
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        test::check(6 - 1 == 5);
        test::check(array, array + 8, [](auto x){ return x < 8; });
    });

    // ================================================
    //  The binary assertions test::check_equal,
    //  test::check_not_equal, test::check_greater,
    //  test::check_not_greater, test::check_less
    //  and test::check_not_less use relational
    //  operators ==, !=, >, <=, <, >= respectively.
    //  Range-based overloads of test::check_equal and
    //  test::check_not_equal use == and != too.
    // ================================================

    test::unit("test::check_<rel>", []{
        int array[] = {0, 1, 2, 3, 4};
        int other[] = {0, 1, 2, 4, 4};
        test::check_equal(2, 2);
        test::check_not_equal(2, 5);
        test::check_greater(4, 2);
        test::check_not_greater(2, 4);
        test::check_less(2, 4);
        test::check_not_less(4, 2);
        test::check_equal(array, array + 5, array);
        test::check_not_equal(array, array + 5, other);
    });

    // ================================================
    //  The test::check_throws and
    //  test::check_nothrows functions accept a
    //  callable object with (optional) arguments and
    //  run it inside a try-catch block.
    // ================================================

    test::unit("test::check_(no)throws", []{
        test::check_throws([]{ throw 0; });
        test::check_nothrows([]{ return 0; });
    });

    // ================================================
    //  To check if a range is sorted, use the
    //  test::check_sorted assertion (duh) which works
    //  on forward iterators.
    // ================================================

    test::unit("test::check_sorted", []{
        int array[] = {0, 1, 2, 3, 4, 5};
        int other[] = {5, 5, 4, 4, 3, 3};
        test::check_sorted(array, array + 6, [](auto x, auto y) { return x < y; });
        test::check_sorted(other, other + 6, [](auto x, auto y) { return x >= y; });
    });

    // ================================================
    //  To ensure an item is present in a range, use
    //  test::check_contains (also works on forward
    //  iterators).
    // ================================================

    test::unit("test::check_contains", []{
        int array[] = {5, 5, 4, 4, 3, 3};
        test::check_contains(array, array + 6, 4);
        test::check_contains(array, array + 6, 3);
        test::check_contains(array, array + 6, 5);
    });

    // ================================================
    //  To turn test::check_* into test::require_*,
    //  you can use the returned value of an assertion
    //  to throw an exception in order to exit out
    //  of the current unit (with an error).
    // ================================================

    test::unit("test::require_*", []{
        int array[] = {5, 5, 4, 4, 3, 3};
        if (!test::check_contains(array, array + 6, 2)) throw 0;
        test::check_sorted(array, array + 6, [](auto x, auto y) { return x >= y; });
    });

});
