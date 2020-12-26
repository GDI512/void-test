#include <void_test.hpp>
#include "common.hpp"

#include <memory>

// clang-format off

int main() {

test::unit("main unit", [](){

    using test::resource;
    using test::core::verifier;

    constexpr auto count = 64;

    resource array[count];

    CHECK(verifier::current().data().destroyed == 0);
    CHECK(verifier::current().data().constructed == count);
    CHECK(verifier::current().data().destructor_errors == 0);
    CHECK(verifier::current().data().constructor_errors == 0);
    CHECK(verifier::current().data().operator_errors == 0);

    std::destroy(std::begin(array), std::end(array));

    CHECK(verifier::current().data().destroyed == count);
    CHECK(verifier::current().data().constructed == count);
    CHECK(verifier::current().data().destructor_errors == 0);
    CHECK(verifier::current().data().constructor_errors == 0);
    CHECK(verifier::current().data().operator_errors == 0);

    std::destroy(std::begin(array), std::end(array));

    CHECK(verifier::current().data().destroyed == count * 2);
    CHECK(verifier::current().data().constructed == count);
    CHECK(verifier::current().data().destructor_errors == count);
    CHECK(verifier::current().data().constructor_errors == 0);
    CHECK(verifier::current().data().operator_errors == 0);

    resource other[count];

    CHECK(verifier::current().data().destroyed == count * 2);
    CHECK(verifier::current().data().constructed == count * 2);
    CHECK(verifier::current().data().destructor_errors == count);
    CHECK(verifier::current().data().constructor_errors == 0);
    CHECK(verifier::current().data().operator_errors == 0);

    std::uninitialized_copy(std::begin(array), std::end(array), std::begin(other));

    CHECK(verifier::current().data().destroyed == count * 2);
    CHECK(verifier::current().data().constructed == count * 3);
    CHECK(verifier::current().data().destructor_errors == count);
    CHECK(verifier::current().data().constructor_errors == count);
    CHECK(verifier::current().data().operator_errors == 0);

    std::copy(std::begin(array), std::end(array), std::begin(other));

    CHECK(verifier::current().data().destroyed == count * 2);
    CHECK(verifier::current().data().constructed == count * 3);
    CHECK(verifier::current().data().destructor_errors == count);
    CHECK(verifier::current().data().constructor_errors == count);
    CHECK(verifier::current().data().operator_errors == count);

});

}

// clang-format on
