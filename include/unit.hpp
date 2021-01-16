#ifndef VOID_TEST_UNIT_HPP
#define VOID_TEST_UNIT_HPP

#include "state.hpp"
#include "output.hpp"
#include "utility.hpp"

namespace void_test {

    template <typename callable>
    auto unit(string name, callable&& content) noexcept -> bool {
        auto scope = core::scope(name);
        auto output = core::output();
        auto registry = core::registry();
        auto verifier = core::verifier();
        try {
            content();
        } catch (...) {
            core::registry::on_exception(name);
        }
        return core::registry::status() && core::verifier::status();
    }

}

#endif
