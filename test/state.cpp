// -----------------------------------------------------------------------------
//  Test file for general functions managing global state of a test.
//      1. Check if marking one assertion as passed doesn't fail the whole test
//         for whatever reason
//      2. Check if marking one assertion as failed fails the entire test after
//         registry object gets destroyed
// -----------------------------------------------------------------------------

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

using void_test::core::registry;

int main() {
    { // 1.
        {
            registry object;
            object.on_success();
        }
        assert(void_test::exit_status() == void_test::exit_success);
    }
    { // 2.
        {
            registry object;
            object.on_error();
        }
        assert(void_test::exit_status() == void_test::exit_failure);
    }
}
