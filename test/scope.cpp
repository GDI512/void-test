// -----------------------------------------------------------------------------
//  Test file for the scope class (used to remember what scope objects of its
//  type were defined in).
//      1. Check if a scope object is appended to a static_list correctly
//      2. Check if the string scope was constructed with is still there
// -----------------------------------------------------------------------------

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <cstring>

using void_test::core::scope;

int main() {
    { // 1.
        scope object("scope");
        assert(&scope::current() == &object);
    }
    { // 2.
        scope object("scope");
        assert(strcmp(object.data(), "scope") == 0);
    }
}
