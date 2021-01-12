// ============================================================================
//  Content:
//      Test file for general functions managing global state of a test.
//  Tests:
//      1. Check if the exit_status() returns exit_success by default
//      2. Check if the exit_status() overload sets the exit code properly
//      3. Check if marking one assertion as passed doesn't fail the whole test
//         for whatever reason
//      4. Make sure an untouched verifier does not cause a test failure
//      5. Check if marking one assertion as failed fails the entire test after
//         registry object gets destroyed
//      6. Check if a destructor error fails the test on verifier's destruction
//      7. Check if a constructor error fails the test on verifier's
//         destruction
//      8. Check if an operator error fails the test on verifier's destruction
//      9. Check if an irregularity in resource object count causes a test
//         failure
//     10. Check if adding and retrieving test info to / from global state
//         works as expected
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

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
        registry::on_success();
        registry::on_error();
        global::add_test_state(registry::data());
        assert(global::test_state().error_count == 1);
        assert(global::test_state().success_count == 1);
    }
}
