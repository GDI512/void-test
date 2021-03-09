#ifndef CPPLTF_UNIT_HPP
#define CPPLTF_UNIT_HPP

#include "state.hpp"
#include "output.hpp"

namespace test {

    template <typename invocable>
    auto unit(string name, invocable function) noexcept -> int {
        auto registry = core::registry();
        auto output = core::output(name, registry);
        try {
            function();
        } catch (...) {
            core::registry::on_exception();
            core::output::on_exception(name);
        }
        return 0;
    }

}

#endif
