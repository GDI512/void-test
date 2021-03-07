// ================================================================
//    The test::unit function is used for grouping assertions and
//  other test-related code into logical units. It accepts a
//  string which is printed to stdout and a function object
//  to be executed in its context. Because <cppltf> defines its
//  own entry point, test::unit also returns a placeholder integer
//  that makes it possible to define tests by dynamically
//  initializing global variables.
//    Keep in mind that nearly everything in test:: namespace
//  needs to be run inside a lambda (or other function) passed to
//  test::unit as seen in the example below. You can define more
//  than one test-variable but you should not do it across
//  multiple translation units
// ================================================================

#include <cppltf.hpp>

const auto group = test::unit("<group>", []{

    test::unit("<case>", []{
        test::check(true);
        test::check(true);
        test::check(true);
    });

    test::unit("<case>", []{
        test::check(false);
        test::check(true);
        test::check(true);
    });

    test::check(false);
    test::check(false);

    test::unit("<case>", []{
        test::check(true);
        test::check(true);
        test::check(false);
    });

});

// ================================================================
//    Note - an uncaught exception thrown inside a unit gets
//  caught by that unit and counts as an assertion failure.
// ================================================================

const auto other = test::unit("<other>", []{

    test::unit("<case>", []{
        test::check(true);
        test::check(true);
    });

    test::unit("<case>", []{
        test::check(true);
        test::check(true);
    });

});

// ================================================================
//    The code above will result in the following message being
//  printed to console (except in color):
//
//    (unit <group>)
//      (unit <case>)
//        (ok check)
//        (ok check)
//        (ok check)
//        (test ok) [0/3]
//      (unit <case>)
//        (error check)
//        (ok check)
//        (ok check)
//        (test error) [1/3]
//      (error check)
//      (error check)
//      (unit <case>)
//        (ok check)
//        (ok check)
//        (error check)
//        (test error) [1/3]
//      (test error) [2/2]
//    (unit <other>)
//      (unit <case>)
//        (ok check)
//        (ok check)
//        (test ok) [0/2]
//      (unit <case>)
//        (ok check)
//        (ok check)
//        (test ok) [0/2]
//
//  The first value in brackets represents the amount of failed
//  assertions. The second is the total number of assertions
//  executed within the enclosing unit.
// ================================================================
