// ================================================================
//    This file contains examples of all available assertions.
//  In citrine every assertion is defined as a function returning
//  true on success and false on failure.
// ================================================================

#include <citrine.hpp>

const auto unit = citrine::unit("assertions", []{

    // ================================================
    //  The citrine::check assertion has overloads for
    //  pure bool expressions or ranges delimited by
    //  iterators.
    // ================================================

    citrine::unit("citrine::check", []{
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        citrine::check(6 - 1 == 5);
        citrine::check(array, array + 8, [](auto x){ return x < 8; });
    });

    // ================================================
    //  The binary assertions citrine::check_equal,
    //  citrine::check_not_equal, citrine::check_greater,
    //  citrine::check_not_greater, citrine::check_less
    //  and citrine::check_not_less use relational
    //  operators ==, !=, >, <=, <, >= respectively.
    //  Range-based overloads of citrine::check_equal and
    //  citrine::check_not_equal use == and != too.
    // ================================================

    citrine::unit("citrine::check_<rel>", []{
        int array[] = {0, 1, 2, 3, 4};
        int other[] = {0, 1, 2, 4, 4};
        citrine::check_equal(2, 2);
        citrine::check_not_equal(2, 5);
        citrine::check_greater(4, 2);
        citrine::check_not_greater(2, 4);
        citrine::check_less(2, 4);
        citrine::check_not_less(4, 2);
        citrine::check_equal(array, array + 5, array);
        citrine::check_not_equal(array, array + 5, other);
    });

    // ================================================
    //  The citrine::check_throws and
    //  citrine::check_nothrows functions accept a
    //  callable object with (optional) arguments and
    //  run it inside a try-catch block.
    // ================================================

    citrine::unit("citrine::check_(no)throws", []{
        citrine::check_throws([]{ throw 0; });
        citrine::check_nothrows([]{ return 0; });
    });

    // ================================================
    //  To check if a range is sorted, use the
    //  citrine::check_sorted assertion which works on
    //  forward iterators.
    // ================================================

    citrine::unit("citrine::check_sorted", []{
        int array[] = {0, 1, 2, 3, 4, 5};
        int other[] = {5, 5, 4, 4, 3, 3};
        citrine::check_sorted(array, array + 6, [](auto x, auto y) { return x < y; });
        citrine::check_sorted(other, other + 6, [](auto x, auto y) { return x >= y; });
    });

    // ================================================
    //  To ensure an item is present in a range, use
    //  citrine::check_contains (also works on forward
    //  iterators).
    // ================================================

    citrine::unit("citrine::check_contains", []{
        int array[] = {5, 5, 4, 4, 3, 3};
        citrine::check_contains(array, array + 6, 4);
        citrine::check_contains(array, array + 6, 3);
        citrine::check_contains(array, array + 6, 5);
    });

    // ================================================
    //  To turn citrine::check_* into "citrine::require_*",
    //  you can use the returned value of an assertion
    //  to throw an exception in order to exit out
    //  of the current unit (with an error).
    // ================================================

    citrine::unit("citrine::require_*", []{
        int array[] = {5, 5, 4, 4, 3, 3};
        if (!citrine::check_contains(array, array + 6, 2)) throw 0;
        citrine::check_sorted(array, array + 6, [](auto x, auto y) { return x >= y; });
    });

});
