#include <void_test.hpp>
#include "common.hpp"

// clang-format off

int main() {

    test::unit("main unit", [](){

        test::unit("scope unit", [](){

            using test::core::scope;

            CHECK_STREQUAL(scope::current().data(), "scope unit");

        });

        test::unit("registry unit", [](){

            using test::core::test_registry;

            CHECK(test_registry::current().status());
            CHECK(test_registry::current().data().passed == 0);
            CHECK(test_registry::current().data().failed == 0);

            CHECK(test_registry::current().on_success() == 0);
            CHECK(test_registry::current().on_success() == 1);
            CHECK(test_registry::current().on_success() == 2);

            CHECK(test_registry::current().status());
            CHECK(test_registry::current().data().passed == 3);
            CHECK(test_registry::current().data().failed == 0);

            CHECK(test_registry::current().on_error() == 0);
            CHECK(test_registry::current().on_error() == 1);
            CHECK(test_registry::current().on_error() == 2);

            CHECK(!test_registry::current().status());
            CHECK(test_registry::current().data().passed == 3);
            CHECK(test_registry::current().data().failed == 3);

        });

        test::unit("verifier unit", [](){

            using test::core::resource_verifier;

            CHECK(resource_verifier::current().status());
            CHECK(resource_verifier::current().data().destroyed == 0);
            CHECK(resource_verifier::current().data().constructed == 0);
            CHECK(resource_verifier::current().data().destructor_errors == 0);
            CHECK(resource_verifier::current().data().constructor_errors == 0);
            CHECK(resource_verifier::current().data().operator_errors == 0);

            CHECK(resource_verifier::current().on_construction() == 0);
            CHECK(resource_verifier::current().on_construction() == 1);
            CHECK(resource_verifier::current().on_construction() == 2);

            CHECK(!resource_verifier::current().status());
            CHECK(resource_verifier::current().data().destroyed == 0);
            CHECK(resource_verifier::current().data().constructed == 3);
            CHECK(resource_verifier::current().data().destructor_errors == 0);
            CHECK(resource_verifier::current().data().constructor_errors == 0);
            CHECK(resource_verifier::current().data().operator_errors == 0);

            CHECK(resource_verifier::current().on_destruction() == 0);
            CHECK(resource_verifier::current().on_destruction() == 1);
            CHECK(resource_verifier::current().on_destruction() == 2);

            CHECK(resource_verifier::current().status());
            CHECK(resource_verifier::current().data().destroyed == 3);
            CHECK(resource_verifier::current().data().constructed == 3);
            CHECK(resource_verifier::current().data().destructor_errors == 0);
            CHECK(resource_verifier::current().data().constructor_errors == 0);
            CHECK(resource_verifier::current().data().operator_errors == 0);

            CHECK(resource_verifier::current().on_destructor_error() == 0);
            CHECK(resource_verifier::current().on_destructor_error() == 1);
            CHECK(resource_verifier::current().on_destructor_error() == 2);

            CHECK(!resource_verifier::current().status());
            CHECK(resource_verifier::current().data().destroyed == 3);
            CHECK(resource_verifier::current().data().constructed == 3);
            CHECK(resource_verifier::current().data().destructor_errors == 3);
            CHECK(resource_verifier::current().data().constructor_errors == 0);
            CHECK(resource_verifier::current().data().operator_errors == 0);

            CHECK(resource_verifier::current().on_constructor_error() == 0);
            CHECK(resource_verifier::current().on_constructor_error() == 1);
            CHECK(resource_verifier::current().on_constructor_error() == 2);

            CHECK(!resource_verifier::current().status());
            CHECK(resource_verifier::current().data().destroyed == 3);
            CHECK(resource_verifier::current().data().constructed == 3);
            CHECK(resource_verifier::current().data().destructor_errors == 3);
            CHECK(resource_verifier::current().data().constructor_errors == 3);
            CHECK(resource_verifier::current().data().operator_errors == 0);

            CHECK(resource_verifier::current().on_operator_error() == 0);
            CHECK(resource_verifier::current().on_operator_error() == 1);
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
