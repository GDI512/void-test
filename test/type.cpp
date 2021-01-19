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

#include "common.hpp"

#define cassert(x)                                                                                                     \
    if (!(x)) {                                                                                                        \
        print(__LINE__, #x);                                                                                           \
        stop(1);                                                                                                       \
    }

#include <new>
#include <memory>

using namespace void_test;
using namespace void_test::core;

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
}
