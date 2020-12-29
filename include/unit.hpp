#ifndef VOID_TEST_UNIT_HPP
#define VOID_TEST_UNIT_HPP

#include "scope.hpp"
#include "verifier.hpp"
#include "registry.hpp"
#include "output.hpp"
#include "utility.hpp"

namespace void_test {

    template <typename F>
    auto unit(string name, F&& content) noexcept -> bool {
        auto scope = core::scope(name);
        auto output = core::output();
        auto registry = core::registry();
        auto verifier = core::verifier();
        try {
            content();
        } catch (...) {
            core::registry::current().on_error();
            core::output::on_exception(name);
        }
        return registry.status() && verifier.status();
    }

}

#endif
