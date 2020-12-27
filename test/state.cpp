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

            using test::core::registry;

            CHECK(registry::current().status());
            CHECK(registry::current().data().passed == 0);
            CHECK(registry::current().data().failed == 0);

            CHECK(registry::on_success() == 0);
            CHECK(registry::on_success() == 1);
            CHECK(registry::on_success() == 2);

            CHECK(registry::current().status());
            CHECK(registry::current().data().passed == 3);
            CHECK(registry::current().data().failed == 0);

            CHECK(registry::on_error() == 0);
            CHECK(registry::on_error() == 1);
            CHECK(registry::on_error() == 2);

            CHECK(!registry::current().status());
            CHECK(registry::current().data().passed == 3);
            CHECK(registry::current().data().failed == 3);

        });

        test::unit("verifier unit", [](){

            using test::core::verifier;

            CHECK(verifier::current().status());
            CHECK(verifier::current().data().destroyed == 0);
            CHECK(verifier::current().data().constructed == 0);
            CHECK(verifier::current().data().destructor_errors == 0);
            CHECK(verifier::current().data().constructor_errors == 0);
            CHECK(verifier::current().data().operator_errors == 0);

            CHECK(verifier::on_contruction() == 0);
            CHECK(verifier::on_contruction() == 1);
            CHECK(verifier::on_contruction() == 2);

            CHECK(!verifier::current().status());
            CHECK(verifier::current().data().destroyed == 0);
            CHECK(verifier::current().data().constructed == 3);
            CHECK(verifier::current().data().destructor_errors == 0);
            CHECK(verifier::current().data().constructor_errors == 0);
            CHECK(verifier::current().data().operator_errors == 0);

            CHECK(verifier::on_destruction() == 0);
            CHECK(verifier::on_destruction() == 1);
            CHECK(verifier::on_destruction() == 2);

            CHECK(verifier::current().status());
            CHECK(verifier::current().data().destroyed == 3);
            CHECK(verifier::current().data().constructed == 3);
            CHECK(verifier::current().data().destructor_errors == 0);
            CHECK(verifier::current().data().constructor_errors == 0);
            CHECK(verifier::current().data().operator_errors == 0);

            CHECK(verifier::on_destructor_error() == 0);
            CHECK(verifier::on_destructor_error() == 1);
            CHECK(verifier::on_destructor_error() == 2);

            CHECK(!verifier::current().status());
            CHECK(verifier::current().data().destroyed == 3);
            CHECK(verifier::current().data().constructed == 3);
            CHECK(verifier::current().data().destructor_errors == 3);
            CHECK(verifier::current().data().constructor_errors == 0);
            CHECK(verifier::current().data().operator_errors == 0);

            CHECK(verifier::on_constructor_error() == 0);
            CHECK(verifier::on_constructor_error() == 1);
            CHECK(verifier::on_constructor_error() == 2);

            CHECK(!verifier::current().status());
            CHECK(verifier::current().data().destroyed == 3);
            CHECK(verifier::current().data().constructed == 3);
            CHECK(verifier::current().data().destructor_errors == 3);
            CHECK(verifier::current().data().constructor_errors == 3);
            CHECK(verifier::current().data().operator_errors == 0);

            CHECK(verifier::on_operator_error() == 0);
            CHECK(verifier::on_operator_error() == 1);
            CHECK(verifier::on_operator_error() == 2);

            CHECK(!verifier::current().status());
            CHECK(verifier::current().data().destroyed == 3);
            CHECK(verifier::current().data().constructed == 3);
            CHECK(verifier::current().data().destructor_errors == 3);
            CHECK(verifier::current().data().constructor_errors == 3);
            CHECK(verifier::current().data().operator_errors == 3);

        });

    });

}

// clang-format on
