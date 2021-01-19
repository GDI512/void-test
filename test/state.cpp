// ============================================================================
//  Test file for classes managing the internal state of the library.
//       1. Ensure global exit status is `exit_success` by default
//       2. Ensure global exit status can be set properly
//       3. Ensure reporting a success to test registry does not fail the test
//       4. Ensure constructing an empty verifier does not fail the test
//       5. Ensure reporting an error to test registry fails the test
//       6. Ensure reporting a destructor error to verifier fails the test
//       7. Ensure reporting a constructor error to verifier fails the test
//       8. Ensure reporting an operator error to verifier fails the test
//       9. Ensure uneven number of resource ctor and dtor calls fails the test
//      10. Ensure registry gets appended to a static list on construction
//      11. Ensure registry is properly initialized
//      12. Ensure the on-error function modifies registry's state properly
//      13. Ensure the on-success function modifies registry's state properly
//      14. Ensure the on-exception function modifies registry's state properly
//      15. Ensure verifier gets appended to a static list on construction
//      16. Ensure verifier is properly initialized
//      17. Test verifier's state change on resource construction
//      18. Test verifier's state change on resource destruction
//      19. Test verifier's state change on resource destructor errors
//      20. Test verifier's state change on resource constructor errors
//      21. Test verifier's state change on resource operator errors
//      22. Ensure proper resource management does not change verifier's status
//      23. Ensure bad resource management changes verifier's status
//      24. Ensure scope object gets appended to a static list on construction
//      25. Ensure scope object contains the c-string it was constructed with
// ============================================================================

// clang-format off

#include <void_test.hpp>

#include <cstdio>
#include <cstring>
#include <cstdlib>

#define cassert(x) if (!(x)) { printf("Line: %i %s\n", __LINE__, #x); exit(1); }

using namespace void_test;
using namespace void_test::core;

int main() {
    { // 1.
        cassert(global::exit_status() == exit_success);
    }
    { // 2.
        {
            global::exit_status(64);
            cassert(global::exit_status() == 64);
        }
        global::exit_status(exit_success);
    }
    { // 3.
        {
            registry object;
            registry::on_success();
        }
        cassert(global::exit_status() == exit_success);
        global::exit_status(exit_success);
    }
    { // 4.
        { verifier object; }
        cassert(global::exit_status() == exit_success);
        global::exit_status(exit_success);
    }
    { // 5.
        {
            registry object;
            registry::on_error();
        }
        cassert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 6.
        {
            verifier object;
            verifier::on_destructor_error();
        }
        cassert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 7.
        {
            verifier object;
            verifier::on_constructor_error();
        }
        cassert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 8.
        {
            verifier object;
            verifier::on_operator_error();
        }
        cassert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 9.
        {
            verifier object;
            verifier::on_construction();
            verifier::on_construction();
            verifier::on_destruction();
        }
        cassert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 10.
        registry object;
        cassert(&registry::current() == &object);
    }
    { // 11.
        registry object;
        cassert(registry::empty());
        cassert(registry::status());
        cassert(registry::data().success_count == 0);
        cassert(registry::data().error_count == 0);
    }
    { // 12.
        registry object;
        cassert(registry::on_error() == 0);
        cassert(registry::on_error() == 1);
        cassert(!registry::empty());
        cassert(!registry::status());
        cassert(registry::data().success_count == 0);
        cassert(registry::data().error_count == 2);
    }
    { // 13.
        registry object;
        cassert(registry::on_success() == 0);
        cassert(registry::on_success() == 1);
        cassert(!registry::empty());
        cassert(registry::status());
        cassert(registry::data().success_count == 2);
        cassert(registry::data().error_count == 0);
    }
    { // 14.
        registry object;
        cassert(registry::on_exception() == 0);
        cassert(registry::on_exception() == 1);
        cassert(!registry::empty());
        cassert(!registry::status());
        cassert(registry::data().success_count == 0);
        cassert(registry::data().error_count == 2);
    }
    { // 15.
        verifier object;
        cassert(&verifier::current() == &object);
    }
    { // 16.
        verifier object;
        cassert(verifier::empty());
        cassert(verifier::status());
        cassert(verifier::data().destroyed_count == 0);
        cassert(verifier::data().constructed_count == 0);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 17.
        verifier object;
        cassert(verifier::on_construction() == 0);
        cassert(verifier::on_construction() == 1);
        cassert(!verifier::empty());
        cassert(!verifier::status());
        cassert(verifier::data().constructed_count == 2);
    }
    { // 18.
        verifier object;
        cassert(verifier::on_destruction() == 0);
        cassert(verifier::on_destruction() == 1);
        cassert(!verifier::empty());
        cassert(!verifier::status());
        cassert(verifier::data().destroyed_count == 2);
    }
    { // 19.
        verifier object;
        cassert(verifier::on_destructor_error() == 0);
        cassert(verifier::on_destructor_error() == 1);
        cassert(!verifier::status());
        cassert(verifier::data().destructor_error_count == 2);
    }
    { // 20.
        verifier object;
        cassert(verifier::on_constructor_error() == 0);
        cassert(verifier::on_constructor_error() == 1);
        cassert(!verifier::status());
        cassert(verifier::data().constructor_error_count == 2);
    }
    { // 21.
        verifier object;
        cassert(verifier::on_operator_error() == 0);
        cassert(verifier::on_operator_error() == 1);
        cassert(!verifier::status());
        cassert(verifier::data().operator_error_count == 2);
    }
    { // 22.
        verifier object;
        cassert(verifier::on_construction() == 0);
        cassert(verifier::on_destruction() == 0);
        cassert(verifier::status());
    }
    { // 23.
        verifier object;
        cassert(verifier::on_construction() == 0);
        cassert(verifier::on_destruction() == 0);
        cassert(verifier::on_destruction() == 1);
        cassert(!verifier::status());
    }
    { // 24.
        scope object("scope");
        cassert(&scope::current() == &object);
    }
    { // 25.
        scope object("scope");
        cassert(strcmp(scope::data(), "scope") == 0);
    }
}

// clang-format on
