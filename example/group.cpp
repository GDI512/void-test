// ================================================================
//    The test::unit function is used for grouping assertions and
//  other test-related code into logical units. It accepts a
//  string which is printed to stdout and a function object
//  to be executed in its context. Because <cppltf> defines its
//  own entry point, test::unit also returns a placeholder integer
//  that makes it possible to define tests by dynamically
//  initializing a global variable.
//    Keep in mind that nearly everything in test:: namespace
//  needs to be run inside a lambda (or other function) passed to
//  test::unit. The example below shows how to use test::unit
//  properly.
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
//    You can define more than one test-variable but it is not
//  recommended to do so across multiple translation units
// ================================================================

const auto other = test::unit("<other-group>", []{

    test::unit("<case>", []{
        test::check(true);
        test::check(true);
    });

    test::unit("<case>", []{
        test::check(true);
        test::check(true);
    });

});

auto aaa = test::unit("aaa", [](){});

// ================================================================
//
// ================================================================
