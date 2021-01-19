// ============================================================================
//  Test file for test types provided by the library.
//      1. Ensure resource reports its constructor call
//      2. Ensure resource reports its destructor call
//      3. Ensure resource reports an error on double destruction
//      4. Ensure resource reports an error on copy construction from an
//         invalid object
//      5. Ensure resource reports an error on copy assignment from an invalid
//         object
//      6. Ensure resource reports an error on move construction from an
//         invalid object
//      7. Ensure resource reports an error on move assignment from an invalid
//         object
//      8. Ensure resource reports an error on a destructor call into an
//         already initialized memory area
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <new>
#include <utility>
#include <cassert>

using namespace void_test;
using namespace void_test::core;

int main() {
    { // 1.
        byte* objbuf = new byte[64];
        verifier state;
        new (objbuf) resource();
        assert(verifier::data().destroyed_count == 0);
        assert(verifier::data().constructed_count == 1);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
        delete[] objbuf;
    }
    { // 2.
        byte* objbuf = new byte[64];
        verifier state;
        new (objbuf) resource();
        reinterpret_cast<resource*>(objbuf)->~resource();
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 1);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
        delete[] objbuf;
    }
    { // 3.
        byte* objbuf = new byte[64];
        verifier state;
        new (objbuf) resource();
        reinterpret_cast<resource*>(objbuf)->~resource();
        reinterpret_cast<resource*>(objbuf)->~resource();
        assert(verifier::data().destroyed_count == 2);
        assert(verifier::data().constructed_count == 1);
        assert(verifier::data().destructor_error_count == 1);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
        delete[] objbuf;
    }
    { // 4.
        byte* objbuf = new byte[64];
        byte* othbuf = new byte[64];
        verifier state;
        new (objbuf) resource();
        reinterpret_cast<resource*>(objbuf)->~resource();
        new (othbuf) resource(reinterpret_cast<resource&>(*objbuf));
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 1);
        assert(verifier::data().operator_error_count == 0);
        delete[] objbuf;
        delete[] othbuf;
    }
    { // 5.
        byte* objbuf = new byte[64];
        byte* othbuf = new byte[64];
        verifier state;
        new (objbuf) resource();
        new (othbuf) resource();
        reinterpret_cast<resource*>(objbuf)->~resource();
        reinterpret_cast<resource&>(*othbuf) = reinterpret_cast<resource&>(*objbuf);
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 1);
        delete[] objbuf;
        delete[] othbuf;
    }
    { // 6.
        byte* objbuf = new byte[64];
        byte* othbuf = new byte[64];
        verifier state;
        new (objbuf) resource();
        reinterpret_cast<resource*>(objbuf)->~resource();
        // resource other(std::move(object));
        new (othbuf) resource(std::move(reinterpret_cast<resource&>(*objbuf)));
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 1);
        assert(verifier::data().operator_error_count == 0);
        delete[] objbuf;
        delete[] othbuf;
    }
    { // 7.
        byte* objbuf = new byte[64];
        byte* othbuf = new byte[64];
        verifier state;
        new (objbuf) resource();
        new (othbuf) resource();
        reinterpret_cast<resource*>(objbuf)->~resource();
        reinterpret_cast<resource&>(*othbuf) = std::move(reinterpret_cast<resource&>(*objbuf));
        assert(verifier::data().destroyed_count == 1);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 1);
        delete[] objbuf;
        delete[] othbuf;
    }
    { // 8.
        byte* objbuf = new byte[64];
        verifier state;
        new (objbuf) resource();
        new (objbuf) resource();
        assert(verifier::data().destroyed_count == 0);
        assert(verifier::data().constructed_count == 2);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 1);
        assert(verifier::data().operator_error_count == 0);
        delete[] objbuf;
    }
}
