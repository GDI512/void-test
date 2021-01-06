// ============================================================================
//  Content:
//      Test file for the verifier class.
//      It's there to keep track of special resource objects used for testing
//      containers and other RAII classes.
//  Tests:
//      1. Check if a verifier object appends itself to a static list correctly
//      2. Check if a verifier object is properly initialized
//      3. Check if the on_construction() function modifies verifier's state
//         properly
//      4. Check if the on_destruction() function modifies verifier's state
//         properly
//      5. Check if the on_destructor_error() function modifies verifier's
//         state properly
//      6. Check if the on_constructor_error() function modifies verifier's
//         state properly
//      7. Check if the on_operator_error() function modifies verifier's state
//         properly
//      8. Check if a call to status() returns `true` when an equal amount
//         of objects was constructed and destroyed
//      9. Check if a call to status() returns `false` regardless of the amount
//         of constructed / destroyed objects if there was an error
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

using void_test::core::verifier;

int main() {
    { // 1.
        verifier object;
        assert(&verifier::current() == &object);
    }
    { // 2.
        verifier object;
        assert(verifier::empty());
        assert(verifier::status());
        assert(verifier::data().destroyed == 0);
        assert(verifier::data().constructed == 0);
        assert(verifier::data().destructor_errrors == 0);
        assert(verifier::data().constructor_errors == 0);
        assert(verifier::data().operator_errors == 0);
    }
    { // 3.
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_construction() == 1);
        assert(!verifier::empty());
        assert(!verifier::status());
        assert(verifier::data().constructed == 2);
    }
    { // 4.
        verifier object;
        assert(verifier::on_destruction() == 0);
        assert(verifier::on_destruction() == 1);
        assert(!verifier::empty());
        assert(!verifier::status());
        assert(verifier::data().destroyed == 2);
    }
    { // 5.
        verifier object;
        assert(verifier::on_destructor_error() == 0);
        assert(verifier::on_destructor_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().destructor_errrors == 2);
    }
    { // 6.
        verifier object;
        assert(verifier::on_constructor_error() == 0);
        assert(verifier::on_constructor_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().constructor_errors == 2);
    }
    { // 7.
        verifier object;
        assert(verifier::on_operator_error() == 0);
        assert(verifier::on_operator_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().operator_errors == 2);
    }
    { // 8.
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_destruction() == 0);
        assert(verifier::status());
    }
    { // 9.
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_destruction() == 0);
        assert(verifier::on_destructor_error() == 0);
        assert(!verifier::status());
    }
}