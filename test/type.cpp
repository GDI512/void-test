// ============================================================================
//  Test file for test types provided by the library.
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
    {
        verifier state;
        resource object;
        assert(verifier::data().destroyed_count == 0);
        assert(verifier::data().constructed_count == 1);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
    }
    {
        verifier state;
        resource object;
        object.~resource();
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 1);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
    }
    {
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
    {
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
    {
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
    {
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
    {
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
    {
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
