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

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <cstring>

using namespace void_test;
using namespace void_test::core;

int main() {
    { // 1.
        assert(global::exit_status() == exit_success);
    }
    { // 2.
        {
            global::exit_status(64);
            assert(global::exit_status() == 64);
        }
        global::exit_status(exit_success);
    }
    { // 3.
        {
            registry object;
            registry::on_success();
        }
        assert(global::exit_status() == exit_success);
        global::exit_status(exit_success);
    }
    { // 4.
        { verifier object; }
        assert(global::exit_status() == exit_success);
        global::exit_status(exit_success);
    }
    { // 5.
        {
            registry object;
            registry::on_error();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 6.
        {
            verifier object;
            verifier::on_destructor_error();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 7.
        {
            verifier object;
            verifier::on_constructor_error();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 8.
        {
            verifier object;
            verifier::on_operator_error();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 9.
        {
            verifier object;
            verifier::on_construction();
            verifier::on_construction();
            verifier::on_destruction();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    { // 10.
        registry object;
        assert(&registry::current() == &object);
    }
    { // 11.
        registry object;
        assert(registry::empty());
        assert(registry::status());
        assert(registry::data().success_count == 0);
        assert(registry::data().error_count == 0);
    }
    { // 12.
        registry object;
        assert(registry::on_error() == 0);
        assert(registry::on_error() == 1);
        assert(!registry::empty());
        assert(!registry::status());
        assert(registry::data().success_count == 0);
        assert(registry::data().error_count == 2);
    }
    { // 13.
        registry object;
        assert(registry::on_success() == 0);
        assert(registry::on_success() == 1);
        assert(!registry::empty());
        assert(registry::status());
        assert(registry::data().success_count == 2);
        assert(registry::data().error_count == 0);
    }
    { // 14.
        registry object;
        assert(registry::on_exception() == 0);
        assert(registry::on_exception() == 1);
        assert(!registry::empty());
        assert(!registry::status());
        assert(registry::data().success_count == 0);
        assert(registry::data().error_count == 2);
    }
    { // 15.
        verifier object;
        assert(&verifier::current() == &object);
    }
    { // 16.
        verifier object;
        assert(verifier::empty());
        assert(verifier::status());
        assert(verifier::data().destroyed_count == 0);
        assert(verifier::data().constructed_count == 0);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
    }
    { // 17.
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_construction() == 1);
        assert(!verifier::empty());
        assert(!verifier::status());
        assert(verifier::data().constructed_count == 2);
    }
    { // 18.
        verifier object;
        assert(verifier::on_destruction() == 0);
        assert(verifier::on_destruction() == 1);
        assert(!verifier::empty());
        assert(!verifier::status());
        assert(verifier::data().destroyed_count == 2);
    }
    { // 19.
        verifier object;
        assert(verifier::on_destructor_error() == 0);
        assert(verifier::on_destructor_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().destructor_error_count == 2);
    }
    { // 20.
        verifier object;
        assert(verifier::on_constructor_error() == 0);
        assert(verifier::on_constructor_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().constructor_error_count == 2);
    }
    { // 21.
        verifier object;
        assert(verifier::on_operator_error() == 0);
        assert(verifier::on_operator_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().operator_error_count == 2);
    }
    { // 22.
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_destruction() == 0);
        assert(verifier::status());
    }
    { // 23.
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_destruction() == 0);
        assert(verifier::on_destruction() == 1);
        assert(!verifier::status());
    }
    { // 24.
        scope object("scope");
        assert(&scope::current() == &object);
    }
    { // 25.
        scope object("scope");
        assert(strcmp(scope::data(), "scope") == 0);
    }
}
