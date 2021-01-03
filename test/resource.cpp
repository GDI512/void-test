// ============================================================================
//  Content:
//      Test file for the resource class.
//      This class is used to report RAII errors within container classes
//      and similar. Its special member functions call the appropriate
//      functions of the active verifier object.
//  Tests:
//      1. Check if constructing a resource reports a new object
//      2. Check if destroying a resource reports object destruction
//      3. Check if destroying the same object twice reports an error
//      4. Check if copy constructing from a destroyed object reports an error
//      5. Check if copy assignment from a destroyed object reports an error
//      6. Check if move constructing from a destroyed object reports an error
//      7. Check if move assignment from a destroyed object reports an error
//      8. Check if constructing over an existing object reports an error
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <utility>
#include <cassert>

using void_test::resource;
using void_test::core::verifier;

int main() {
    { // 1.
        verifier state;
        resource object;
        assert(state.data().destroyed == 0);
        assert(state.data().constructed == 1);
        assert(state.data().dtor_errors == 0);
        assert(state.data().ctor_errors == 0);
        assert(state.data().op_errors == 0);
    }
    { // 2.
        verifier state;
        resource object;
        object.~resource();
        assert(state.data().destroyed == 1);
        assert(state.data().constructed == 1);
        assert(state.data().dtor_errors == 0);
        assert(state.data().ctor_errors == 0);
        assert(state.data().op_errors == 0);
    }
    { // 3.
        verifier state;
        resource object;
        object.~resource();
        object.~resource();
        assert(state.data().destroyed == 2);
        assert(state.data().constructed == 1);
        assert(state.data().dtor_errors == 1);
        assert(state.data().ctor_errors == 0);
        assert(state.data().op_errors == 0);
    }
    { // 4.
        verifier state;
        resource object;
        object.~resource();
        resource other(object);
        assert(state.data().destroyed == 1);
        assert(state.data().constructed == 2);
        assert(state.data().dtor_errors == 0);
        assert(state.data().ctor_errors == 1);
        assert(state.data().op_errors == 0);
    }
    { // 5.
        verifier state;
        resource object;
        resource other;
        object.~resource();
        other = object;
        assert(state.data().destroyed == 1);
        assert(state.data().constructed == 2);
        assert(state.data().dtor_errors == 0);
        assert(state.data().ctor_errors == 0);
        assert(state.data().op_errors == 1);
    }
    { // 6.
        verifier state;
        resource object;
        object.~resource();
        resource other(std::move(object));
        assert(state.data().destroyed == 1);
        assert(state.data().constructed == 2);
        assert(state.data().dtor_errors == 0);
        assert(state.data().ctor_errors == 1);
        assert(state.data().op_errors == 0);
    }
    { // 7.
        verifier state;
        resource object;
        resource other;
        object.~resource();
        other = std::move(object);
        assert(state.data().destroyed == 1);
        assert(state.data().constructed == 2);
        assert(state.data().dtor_errors == 0);
        assert(state.data().ctor_errors == 0);
        assert(state.data().op_errors == 1);
    }
    { // 8.
        verifier state;
        resource object;
        new (&object) resource();
        assert(state.data().destroyed == 0);
        assert(state.data().constructed == 2);
        assert(state.data().dtor_errors == 0);
        assert(state.data().ctor_errors == 1);
        assert(state.data().op_errors == 0);
    }
}
