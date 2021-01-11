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
        assert(verifier::data().destroyed_count == 0);
        assert(verifier::data().constructed_count == 1);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
    }
    { // 2.
        verifier state;
        resource object;
        object.~resource();
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 1);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
    }
    { // 3.
        verifier state;
        resource object;
        object.~resource();
        object.~resource();
        assert(verifier::data().destroyed_count == 2);
        assert(verifier::data().constructed_count == 1);
        assert(verifier::data().destructor_error_count == 1);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
    }
    { // 4.
        verifier state;
        resource object;
        object.~resource();
        resource other(object);
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 1);
        assert(verifier::data().operator_error_count == 0);
    }
    { // 5.
        verifier state;
        resource object;
        resource other;
        object.~resource();
        other = object;
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 1);
    }
    { // 6.
        verifier state;
        resource object;
        object.~resource();
        resource other(std::move(object));
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 1);
        assert(verifier::data().operator_error_count == 0);
    }
    { // 7.
        verifier state;
        resource object;
        resource other;
        object.~resource();
        other = std::move(object);
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 1);
    }
    { // 8.
        verifier state;
        resource object;
        new (&object) resource();
        assert(verifier::data().destroyed_count == 0);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 1);
        assert(verifier::data().operator_error_count == 0);
    }
}
