#ifndef CPPLTF_UNIT_HPP
#define CPPLTF_UNIT_HPP

#include "state.hpp"
#include "output.hpp"

namespace test {

    template <typename T>
    auto unit(core::string name, T&& function) noexcept -> int {
        const auto scope = core::output(name);
        const auto registry = core::registry();
        try {
            function();
        } catch (...) {
            core::registry::on_exception(name);
        }
        return 0;
    }

}

#endif
