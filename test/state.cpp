#include <void_test.hpp>
#include "common.hpp"

// clang-format off

using test::core::scope;
using test::core::test_registry;
using test::core::resource_verifier;

int main() {

test::unit("main unit", [](){

    test::unit("scope unit", [](){

        CHECK_STREQUAL(scope::current().data(), "scope unit"); // current scope object should hold this string

    });

    test::unit("registry unit", [](){

        CHECK(test_registry::current().status());           // In a fresh unit, test is
        CHECK(test_registry::current().data().passed == 0); // successful and no errors or
        CHECK(test_registry::current().data().failed == 0); // new tests are registered.

        CHECK(test_registry::current().on_success() == 0);  // We call on_success() to register
        CHECK(test_registry::current().on_success() == 1);  // a passing test. It returns previous count
        CHECK(test_registry::current().on_success() == 2);  // of passed tests. Three times for good measure.

        CHECK(test_registry::current().status());           // Some tests were conducted but all of
        CHECK(test_registry::current().data().passed == 3); // them have passed so status() still evaluates
        CHECK(test_registry::current().data().failed == 0); // to `true`.

        CHECK(test_registry::current().on_error() == 0);    // on_error() should work similarly
        CHECK(test_registry::current().on_error() == 1);    // to on_success().
        CHECK(test_registry::current().on_error() == 2);

        CHECK(!test_registry::current().status());          // Since some errors were registered,
        CHECK(test_registry::current().data().passed == 3); // status() should no longer evaluate to
        CHECK(test_registry::current().data().failed == 3); // `true`

    });

    test::unit("verifier unit", [](){

        CHECK(resource_verifier::current().status());                 // New unit, resource_verifier's state is ok
        CHECK(resource_verifier::current().data().destroyed == 0);    // and no errors or anything is detected
        CHECK(resource_verifier::current().data().constructed == 0);
        CHECK(resource_verifier::current().data().destructor_errors == 0);
        CHECK(resource_verifier::current().data().constructor_errors == 0);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        CHECK(resource_verifier::current().on_construction() == 0); // We 'construct' three objects
        CHECK(resource_verifier::current().on_construction() == 1); // (those functions would normally
        CHECK(resource_verifier::current().on_construction() == 2); // be called from test::resource)

        CHECK(!resource_verifier::current().status());                      // status() is `false` since
        CHECK(resource_verifier::current().data().destroyed == 0);          // the amount of objects constructed
        CHECK(resource_verifier::current().data().constructed == 3);        // is not equal to the amount of
        CHECK(resource_verifier::current().data().destructor_errors == 0);  // objects destroyed
        CHECK(resource_verifier::current().data().constructor_errors == 0);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        CHECK(resource_verifier::current().on_destruction() == 0);  // We 'destroy' three objects
        CHECK(resource_verifier::current().on_destruction() == 1);
        CHECK(resource_verifier::current().on_destruction() == 2);

        CHECK(resource_verifier::current().status());                       // Everything should be OK now,
        CHECK(resource_verifier::current().data().destroyed == 3);          // all constructed objects have
        CHECK(resource_verifier::current().data().constructed == 3);        // been destroyed
        CHECK(resource_verifier::current().data().destructor_errors == 0);
        CHECK(resource_verifier::current().data().constructor_errors == 0);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        CHECK(resource_verifier::current().on_destructor_error() == 0); // Let's say we got
        CHECK(resource_verifier::current().on_destructor_error() == 1); // some destructor errors here
        CHECK(resource_verifier::current().on_destructor_error() == 2);

        CHECK(!resource_verifier::current().status());                  // status() should no longer
        CHECK(resource_verifier::current().data().destroyed == 3);      // evaluate to `true` from here on
        CHECK(resource_verifier::current().data().constructed == 3);
        CHECK(resource_verifier::current().data().destructor_errors == 3);
        CHECK(resource_verifier::current().data().constructor_errors == 0);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        CHECK(resource_verifier::current().on_constructor_error() == 0);
        CHECK(resource_verifier::current().on_constructor_error() == 1);    // More errors
        CHECK(resource_verifier::current().on_constructor_error() == 2);

        CHECK(!resource_verifier::current().status());
        CHECK(resource_verifier::current().data().destroyed == 3);
        CHECK(resource_verifier::current().data().constructed == 3);
        CHECK(resource_verifier::current().data().destructor_errors == 3);
        CHECK(resource_verifier::current().data().constructor_errors == 3);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        CHECK(resource_verifier::current().on_operator_error() == 0);
        CHECK(resource_verifier::current().on_operator_error() == 1);   // Even more errors
        CHECK(resource_verifier::current().on_operator_error() == 2);

        CHECK(!resource_verifier::current().status());
        CHECK(resource_verifier::current().data().destroyed == 3);
        CHECK(resource_verifier::current().data().constructed == 3);
        CHECK(resource_verifier::current().data().destructor_errors == 3);
        CHECK(resource_verifier::current().data().constructor_errors == 3);
        CHECK(resource_verifier::current().data().operator_errors == 3);

    });

});

}

// clang-format on
