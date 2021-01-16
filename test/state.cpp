// ============================================================================
//  Test file for classes managing the internal state of the library.
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
    {
        assert(global::exit_status() == exit_success);
    }
    {
        {
            global::exit_status(64);
            assert(global::exit_status() == 64);
        }
        global::exit_status(exit_success);
    }
    {
        {
            registry object;
            registry::on_success();
        }
        assert(global::exit_status() == exit_success);
        global::exit_status(exit_success);
    }
    {
        { verifier object; }
        assert(global::exit_status() == exit_success);
        global::exit_status(exit_success);
    }
    {
        {
            registry object;
            registry::on_error();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    {
        {
            verifier object;
            verifier::on_destructor_error();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    {
        {
            verifier object;
            verifier::on_constructor_error();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    {
        {
            verifier object;
            verifier::on_operator_error();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    {
        {
            verifier object;
            verifier::on_construction();
            verifier::on_construction();
            verifier::on_destruction();
        }
        assert(global::exit_status() == exit_failure);
        global::exit_status(exit_success);
    }
    {
        registry object;
        assert(&registry::current() == &object);
    }
    {
        registry object;
        assert(registry::empty());
        assert(registry::status());
        assert(registry::data().success_count == 0);
        assert(registry::data().error_count == 0);
    }
    {
        registry object;
        assert(registry::on_error() == 0);
        assert(registry::on_error() == 1);
        assert(!registry::empty());
        assert(!registry::status());
        assert(registry::data().success_count == 0);
        assert(registry::data().error_count == 2);
    }
    {
        registry object;
        assert(registry::on_success() == 0);
        assert(registry::on_success() == 1);
        assert(!registry::empty());
        assert(registry::status());
        assert(registry::data().success_count == 2);
        assert(registry::data().error_count == 0);
    }
    {
        registry object;
        assert(registry::on_exception() == 0);
        assert(registry::on_exception() == 1);
        assert(!registry::empty());
        assert(!registry::status());
        assert(registry::data().success_count == 0);
        assert(registry::data().error_count == 2);
    }
    {
        verifier object;
        assert(&verifier::current() == &object);
    }
    {
        verifier object;
        assert(verifier::empty());
        assert(verifier::status());
        assert(verifier::data().destroyed_count == 0);
        assert(verifier::data().constructed_count == 0);
        assert(verifier::data().destructor_error_count == 0);
        assert(verifier::data().constructor_error_count == 0);
        assert(verifier::data().operator_error_count == 0);
    }
    {
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_construction() == 1);
        assert(!verifier::empty());
        assert(!verifier::status());
        assert(verifier::data().constructed_count == 2);
    }
    {
        verifier object;
        assert(verifier::on_destruction() == 0);
        assert(verifier::on_destruction() == 1);
        assert(!verifier::empty());
        assert(!verifier::status());
        assert(verifier::data().destroyed_count == 2);
    }
    {
        verifier object;
        assert(verifier::on_destructor_error() == 0);
        assert(verifier::on_destructor_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().destructor_error_count == 2);
    }
    {
        verifier object;
        assert(verifier::on_constructor_error() == 0);
        assert(verifier::on_constructor_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().constructor_error_count == 2);
    }
    {
        verifier object;
        assert(verifier::on_operator_error() == 0);
        assert(verifier::on_operator_error() == 1);
        assert(!verifier::status());
        assert(verifier::data().operator_error_count == 2);
    }
    {
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_destruction() == 0);
        assert(verifier::status());
    }
    {
        verifier object;
        assert(verifier::on_construction() == 0);
        assert(verifier::on_destruction() == 0);
        assert(verifier::on_destructor_error() == 0);
        assert(!verifier::status());
    }
    {
        scope object("scope");
        assert(&scope::current() == &object);
    }
    {
        scope object("scope");
        assert(strcmp(scope::data(), "scope") == 0);
    }
}
