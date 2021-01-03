// ============================================================================
//  Content:
//      Test file for the test registry class.
//      This class is used to keep track of failed and passed assertions
//      within its scope. Used within the unit function.
//  Tests:
//      1. Check if the registry appends itself to a static list correctly
//      2. Check if the registry is properly initialized
//      3. Check if calling on_error() modifies registry's state accordingly
//      3. Check if calling on_success() modifies registry's state accordingly
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

using void_test::core::registry;

int main() {
    { // 1.
        registry object;
        assert(&registry::current() == &object);
    }
    { // 2.
        registry object;
        assert(registry::empty());
        assert(registry::status());
        assert(registry::data().passed == 0);
        assert(registry::data().failed == 0);
    }
    { // 3.
        registry object;
        assert(registry::on_error() == 0);
        assert(registry::on_error() == 1);
        assert(!registry::empty());
        assert(!registry::status());
        assert(registry::data().passed == 0);
        assert(registry::data().failed == 2);
    }
    { // 4.
        registry object;
        assert(registry::on_success() == 0);
        assert(registry::on_success() == 1);
        assert(!registry::empty());
        assert(registry::status());
        assert(registry::data().passed == 2);
        assert(registry::data().failed == 0);
    }
}
