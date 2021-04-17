// ================================================================
//    Because testing container classes for proper resource
//  management tends to be particularly frustrating, citrine
//  defines two auxiliary types for this exact purpose -
//  test::counter and test::object.
//    The test::counter class (the safer option) increments a
//  global counter every time it is instantiated and decrements it
//  on every call to its destructor.
//    The test::object class works very similarly but unlike
//  test::counter, it also detects invalid calls to assignment
//  operators, multiple destructor calls on the same address,
//  constructor calls over constructed objects and copy/move
//  constructions from uninitialized memory. Because of the way
//  it is implemented, it relies heavily on UB and should not be
//  used without running the citrine test suite.
// ================================================================

#include <assert.hpp>
#include <object.hpp>
#include <vector>
#include <new>

using byte = unsigned char;

const auto group = test::unit("raii", []{

    // ================================================
    //    In case you ever wondered how often standard
    //  containers construct and destroy elements.
    //  This here is how both test::counter and
    //  test::object are meant to be used.
    // ================================================

    test::unit("test::counter", []{
        auto vector = std::vector<test::counter>(64);
        test::check_equal(vector.size(), 64);
        test::check_equal(vector.capacity(), 64);
    });

    // ================================================
    //    Both test::counter and test::object are
    //  constructible from and implicitly convertible
    //  to int
    // ================================================

    test::unit("test::vector", []{
        auto vector = std::vector<test::object>(64);
        test::check_equal(vector.size(), 64);
        test::check_equal(vector.capacity(), 64);
        vector.insert(vector.begin() + 4, 1);
        test::check(vector[4] == 1);
        test::check_equal(vector.size(), 65);
        test::check_greater(vector.capacity(), 65);
    });

    // ================================================
    //    The format of the output, whether the
    //  message is "(resource ok ...)" or
    //  "(resource error ...)", is "objects destroyed
    //  / objects constructed / destructor errors
    //  / constructor errors / assignment errors"
    // ================================================

    // ================================================
    //    In this example, we allocate memory for 64
    //  test::objects, construct 32 in that buffer
    //  then shift them by 1 to the right and finally
    //  destroy everything.
    //    If we were dealing with trivial types, this
    //  code would probably work perfectly fine but
    //  since test::object is meant to simulate
    //  complex resources, we get the following error:
    //
    //      (resource error [33/32] [1/0/1])
    //
    //    What it tells us is that in this unit there
    //  were 33 objects destroyed and 32 objects
    //  constructed. There also were 2 errors - one
    //  being an invalid call to a destructor and the
    //  other one - an invalid assignment.
    //    What happened? In the middle loop we tried
    //  to assign a test::object to uninitialized
    //  area in memory (see: the right-most element)
    //  and then we attempted to destroy it. Because
    //  objects are not constructed after an
    //  assignment, both operations ended up being
    //  invalid.
    // ================================================

    test::unit("shift", []{
        auto array = static_cast<test::object*>(::operator new(64 * sizeof(test::object)));
        for (auto i = 0; i < 32; i++)
            new (array + i) test::object();
        for (auto i = 32; i > 0; i--)
            array[i] = array[i - 1];
        for (auto i = 0; i < 33; i++)
            array[i].~object();
        ::operator delete(array);
    });

    // ================================================
    //    Here we fix the issue by constructing
    //  test::object at the 32nd position to prepare
    //  it for the following copy assignment operation
    //
    //      (resource ok [33/33] [0/0/0])
    //
    //  Keep in mind that it is possible to encounter
    //  this type of errors even when the numbers of
    //  destructor and constructor calls are equal.
    //  This is why you should use test::object
    //  instead of test::counter whenever your
    //  implementation handles its UB mechanics
    //  properly.
    // ================================================

    test::unit("shift", []{
        auto array = static_cast<test::object*>(::operator new(64 * sizeof(test::object)));
        for (auto i = 0; i < 32; i++)
            new (array + i) test::object();
        new (array + 32) test::object();
        for (auto i = 32; i > 0; i--)
            array[i] = array[i - 1];
        for (auto i = 0; i < 33; i++)
            array[i].~object();
        ::operator delete(array);
    });

    // ================================================
    //    A simpler example - say we forget that
    //  operator delete[] calls destructors on its
    //  elements for whatever reason. After running
    //  the code below the output should look like
    //  this:
    //
    //      (resource error [128/64 [64/0/0])
    //
    // ================================================

    test::unit("delete", []{
        auto array = new test::object[64];
        for (auto i = 0; i < 64; i++)
            array[i].~object();
        delete[] array;
    });

    // ================================================
    //    And the test::counter version:
    //
    //      (resource error [128/64] [0/0/0])
    //
    // ================================================

    test::unit("delete", []{
        auto array = new test::counter[64];
        for (auto i = 0; i < 64; i++)
            array[i].~counter();
        delete[] array;
    });

});
