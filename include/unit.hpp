#ifndef VOID_TEST_UNIT_HPP
#define VOID_TEST_UNIT_HPP

#include "state.hpp"
#include "output.hpp"
#include "utility.hpp"

namespace test {

    template <typename F>
    auto unit(string name, F&& content) noexcept -> bool {
        auto scope = core::scope(name);
        auto registry = core::test_registry();
        auto verifier = core::resource_verifier();
        auto output = core::output();
        try {
            content();
        } catch (...) {
            core::test_registry::current().on_error();
            core::output::on_exception(name);
        }
        return registry.status() && verifier.status();
    }

}

#endif
