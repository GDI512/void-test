// ============================================================================
//  Test file for test types provided by the library.
//      1. Ensure resource reports its constructor call (dynamic)
//      2. Ensure resource reports its destructor call (dynamic)
//      3. Ensure resource reports an error on double destruction (dynamic)
//      4. Ensure resource reports an error on copy construction from an
//         invalid object (dynamic)
//      5. Ensure resource reports an error on copy assignment from an invalid
//         object (dynamic)
//      6. Ensure resource reports an error on move construction from an
//         invalid object (dynamic)
//      7. Ensure resource reports an error on move assignment from an invalid
//         object (dynamic)
//      8. Ensure resource reports an error on a destructor call into an
//         already initialized memory area (dynamic)
//      9. Ensure resource reports its constructor call (automatic)
//     10. Ensure resource reports its destructor call (automatic)
//     11. Ensure resource reports an error on double destruction (automatic)
//     12. Ensure resource reports an error on copy construction from an
//         invalid object (automatic)
//     13. Ensure resource reports an error on copy assignment from an invalid
//         object (automatic)
//     14. Ensure resource reports an error on move construction from an
//         invalid object (automatic)
//     15. Ensure resource reports an error on move assignment from an invalid
//         object (automatic)
//     16. Ensure resource reports an error on a destructor call into an
//         already initialized memory area (automatic)
// ============================================================================

#include "common.hpp"

#include <new>
#include <memory>

using namespace test;
using namespace test::core;

int main() {
    { // 1.
        auto objbuf = std::make_unique<byte[]>(64);
        verifier state;
        new (objbuf.get()) resource();
        cassert(verifier::data().destroyed_count == 0);
        cassert(verifier::data().constructed_count == 1);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 2.
        auto objbuf = std::make_unique<byte[]>(64);
        verifier state;
        new (objbuf.get()) resource();
        reinterpret_cast<resource*>(objbuf.get())->~resource();
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 1);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 3.
        auto objbuf = std::make_unique<byte[]>(64);
        verifier state;
        new (objbuf.get()) resource();
        reinterpret_cast<resource*>(objbuf.get())->~resource();
        reinterpret_cast<resource*>(objbuf.get())->~resource();
        cassert(verifier::data().destroyed_count == 2);
        cassert(verifier::data().constructed_count == 1);
        cassert(verifier::data().destructor_error_count == 1);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 4.
        auto objbuf = std::make_unique<byte[]>(64);
        auto othbuf = std::make_unique<byte[]>(64);
        verifier state;
        new (objbuf.get()) resource();
        reinterpret_cast<resource*>(objbuf.get())->~resource();
        new (othbuf.get()) resource(reinterpret_cast<resource&>(*objbuf.get()));
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 1);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 5.
        auto objbuf = std::make_unique<byte[]>(64);
        auto othbuf = std::make_unique<byte[]>(64);
        verifier state;
        new (objbuf.get()) resource();
        new (othbuf.get()) resource();
        reinterpret_cast<resource*>(objbuf.get())->~resource();
        reinterpret_cast<resource&>(*othbuf.get()) = reinterpret_cast<resource&>(*objbuf.get());
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 1);
    }
    { // 6.
        auto objbuf = std::make_unique<byte[]>(64);
        auto othbuf = std::make_unique<byte[]>(64);
        verifier state;
        new (objbuf.get()) resource();
        reinterpret_cast<resource*>(objbuf.get())->~resource();
        new (othbuf.get()) resource(std::move(reinterpret_cast<resource&>(*objbuf.get())));
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 1);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 7.
        auto objbuf = std::make_unique<byte[]>(64);
        auto othbuf = std::make_unique<byte[]>(64);
        verifier state;
        new (objbuf.get()) resource();
        new (othbuf.get()) resource();
        reinterpret_cast<resource*>(objbuf.get())->~resource();
        reinterpret_cast<resource&>(*othbuf.get()) = std::move(reinterpret_cast<resource&>(*objbuf.get()));
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 1);
    }
    { // 8.
        auto objbuf = std::make_unique<byte[]>(64);
        verifier state;
        new (objbuf.get()) resource();
        new (objbuf.get()) resource();
        cassert(verifier::data().destroyed_count == 0);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 1);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 9.
        verifier state;
        resource object;
        cassert(verifier::data().destroyed_count == 0);
        cassert(verifier::data().constructed_count == 1);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 10.
        verifier state;
        resource object;
        object.~resource();
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 1);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 11.
        verifier state;
        resource object;
        object.~resource();
        object.~resource();
        cassert(verifier::data().destroyed_count == 2);
        cassert(verifier::data().constructed_count == 1);
        cassert(verifier::data().destructor_error_count == 1);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 12.
        verifier state;
        resource object;
        object.~resource();
        resource other(object);
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 1);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 13.
        verifier state;
        resource object;
        resource other;
        object.~resource();
        other = std::move(object);
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 1);
    }
    { // 14.
        verifier state;
        resource object;
        object.~resource();
        resource other(std::move(object));
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 1);
        cassert(verifier::data().operator_error_count == 0);
    }
    { // 15.
        verifier state;
        resource object;
        resource other;
        object.~resource();
        other = std::move(object);
        cassert(verifier::data().destroyed_count == 1);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 0);
        cassert(verifier::data().operator_error_count == 1);
    }
    { // 16.
        verifier state;
        resource object;
        new (&object) resource();
        cassert(verifier::data().destroyed_count == 0);
        cassert(verifier::data().constructed_count == 2);
        cassert(verifier::data().destructor_error_count == 0);
        cassert(verifier::data().constructor_error_count == 1);
        cassert(verifier::data().operator_error_count == 0);
    }
}
