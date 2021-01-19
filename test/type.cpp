// ============================================================================
//  Test file for test types provided by the library.
//      1. Ensure resource reports its constructor call
//      2. Ensure resource reports its destructor call
//      3. Ensure resource reports an error on double destruction
//      4. Ensure resource reports an error on copy construction from an
//         invalid object
//      5. Ensure resource reports an error on copy assignment from an invalid
//         object
//      6. Ensure resource reports an error on move construction from an
//         invalid object
//      7. Ensure resource reports an error on move assignment from an invalid
//         object
//      8. Ensure resource reports an error on a destructor call into an
//         already initialized memory area
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <new>
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
