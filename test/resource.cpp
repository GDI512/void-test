#include <void_test.hpp>
#include "common.hpp"

#include <memory>

// clang-format off

using test::resource;
using test::core::resource_verifier;

constexpr auto count = 64;

int main() {

test::unit("main unit", [](){

    resource array[count];  // We create the first array of `count` objects...

    CHECK(resource_verifier::current().data().destroyed == 0);          // ...so resource_verifier
    CHECK(resource_verifier::current().data().constructed == count);    // should only register `count`
    CHECK(resource_verifier::current().data().destructor_errors == 0);  // as constructed
    CHECK(resource_verifier::current().data().constructor_errors == 0);
    CHECK(resource_verifier::current().data().operator_errors == 0);

    std::destroy(std::begin(array), std::end(array));   // We destroy the first array

    CHECK(resource_verifier::current().data().destroyed == count);      // `count` objects destroyed,
    CHECK(resource_verifier::current().data().constructed == count);    // that's what resource_verifier
    CHECK(resource_verifier::current().data().destructor_errors == 0);  // should see. No RAII errors yet
    CHECK(resource_verifier::current().data().constructor_errors == 0);
    CHECK(resource_verifier::current().data().operator_errors == 0);

    std::destroy(std::begin(array), std::end(array));   // We destroy the first array a second time

    CHECK(resource_verifier::current().data().destroyed == count * 2);      // `count` * 2 is the expected
    CHECK(resource_verifier::current().data().constructed == count);        // amount of destroyed objects.
    CHECK(resource_verifier::current().data().destructor_errors == count);  // resource_verifier should now
    CHECK(resource_verifier::current().data().constructor_errors == 0);     // see `count` destructor errors
    CHECK(resource_verifier::current().data().operator_errors == 0);

    resource other[count];  // Now we create the second array

    CHECK(resource_verifier::current().data().destroyed == count * 2);      // No errors here, just another
    CHECK(resource_verifier::current().data().constructed == count * 2);    // `count` objects constructed
    CHECK(resource_verifier::current().data().destructor_errors == count);
    CHECK(resource_verifier::current().data().constructor_errors == 0);
    CHECK(resource_verifier::current().data().operator_errors == 0);

    std::uninitialized_copy(std::begin(array), std::end(array), std::begin(other)); // Copy constructors are called

    CHECK(resource_verifier::current().data().destroyed == count * 2);
    CHECK(resource_verifier::current().data().constructed == count * 3);    // The correct amount of constructed
    CHECK(resource_verifier::current().data().destructor_errors == count);  // objects is 3 * `count` because
    CHECK(resource_verifier::current().data().constructor_errors == count); // we copy constructed into an
    CHECK(resource_verifier::current().data().operator_errors == 0);        // initialized area in memory

    std::copy(std::begin(array), std::end(array), std::begin(other));   // Copy assignment from destroyed array

    CHECK(resource_verifier::current().data().destroyed == count * 2);
    CHECK(resource_verifier::current().data().constructed == count * 3);
    CHECK(resource_verifier::current().data().destructor_errors == count);  // No objects constructed this time
    CHECK(resource_verifier::current().data().constructor_errors == count); // but assigning from a destroyed array
    CHECK(resource_verifier::current().data().operator_errors == count);    // is a bad idea

});

}

// clang-format on
