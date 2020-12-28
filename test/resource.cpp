#include <void_test.hpp>
#include "common.hpp"

#include <memory>

// clang-format off

int main() {

    test::unit("main unit", [](){

        using test::resource;
        using test::core::resource_verifier;

        constexpr auto count = 64;

        resource array[count];

        CHECK(resource_verifier::current().data().destroyed == 0);
        CHECK(resource_verifier::current().data().constructed == count);
        CHECK(resource_verifier::current().data().destructor_errors == 0);
        CHECK(resource_verifier::current().data().constructor_errors == 0);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        std::destroy(std::begin(array), std::end(array));

        CHECK(resource_verifier::current().data().destroyed == count);
        CHECK(resource_verifier::current().data().constructed == count);
        CHECK(resource_verifier::current().data().destructor_errors == 0);
        CHECK(resource_verifier::current().data().constructor_errors == 0);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        std::destroy(std::begin(array), std::end(array));

        CHECK(resource_verifier::current().data().destroyed == count * 2);
        CHECK(resource_verifier::current().data().constructed == count);
        CHECK(resource_verifier::current().data().destructor_errors == count);
        CHECK(resource_verifier::current().data().constructor_errors == 0);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        resource other[count];

        CHECK(resource_verifier::current().data().destroyed == count * 2);
        CHECK(resource_verifier::current().data().constructed == count * 2);
        CHECK(resource_verifier::current().data().destructor_errors == count);
        CHECK(resource_verifier::current().data().constructor_errors == 0);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        std::uninitialized_copy(std::begin(array), std::end(array), std::begin(other));

        CHECK(resource_verifier::current().data().destroyed == count * 2);
        CHECK(resource_verifier::current().data().constructed == count * 3);
        CHECK(resource_verifier::current().data().destructor_errors == count);
        CHECK(resource_verifier::current().data().constructor_errors == count);
        CHECK(resource_verifier::current().data().operator_errors == 0);

        std::copy(std::begin(array), std::end(array), std::begin(other));

        CHECK(resource_verifier::current().data().destroyed == count * 2);
        CHECK(resource_verifier::current().data().constructed == count * 3);
        CHECK(resource_verifier::current().data().destructor_errors == count);
        CHECK(resource_verifier::current().data().constructor_errors == count);
        CHECK(resource_verifier::current().data().operator_errors == count);

    });

}

// clang-format on
