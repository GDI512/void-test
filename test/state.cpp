// ============================================================================
//  Content:
//      Test file for general functions managing global state of a test.
//  Tests:
//      1. Check if marking one assertion as passed doesn't fail the whole test
//         for whatever reason
//      2. Make sure an untouched verifier does not cause a test failure
//      3. Check if marking one assertion as failed fails the entire test after
//         registry object gets destroyed
//      4. Check if a destructor error fails the test on verifier's destruction
//      5. Check if a constructor error fails the test on verifier's
//         destruction
//      6. Check if an operator error fails the test on verifier's destruction
//      7. Check if an irregularity in resource object count causes a test
//         failure
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

using void_test::core::registry;
using void_test::core::verifier;

int main() {
    { // 1.
        {
            registry object;
            registry::on_success();
        }
        assert(void_test::exit_status() == void_test::exit_success);
        void_test::core::exit_status = void_test::exit_success;
    }
    { // 2.
        {
            verifier object;
        }
        assert(void_test::exit_status() == void_test::exit_success);
        void_test::core::exit_status = void_test::exit_success;
    }
    { // 3.
        {
            registry object;
            registry::on_error();
        }
        assert(void_test::exit_status() == void_test::exit_failure);
        void_test::core::exit_status = void_test::exit_success;
    }
    { // 4.
        {
            verifier object;
            verifier::on_destructor_error();
        }
        assert(void_test::exit_status() == void_test::exit_failure);
        void_test::core::exit_status = void_test::exit_success;
    }
    { // 5.
        {
            verifier object;
            verifier::on_constructor_error();
        }
        assert(void_test::exit_status() == void_test::exit_failure);
        void_test::core::exit_status = void_test::exit_success;
    }
    { // 6.
        {
            verifier object;
            verifier::on_operator_error();
        }
        assert(void_test::exit_status() == void_test::exit_failure);
        void_test::core::exit_status = void_test::exit_success;
    }
    { // 7.
        {
            verifier object;
            verifier::on_construction();
            verifier::on_construction();
            verifier::on_destruction();
        }
        assert(void_test::exit_status() == void_test::exit_failure);
        void_test::core::exit_status = void_test::exit_success;
    }
}
