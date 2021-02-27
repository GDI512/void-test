#ifndef CPPLTF_UNIT_HPP
#define CPPLTF_UNIT_HPP

#include "state.hpp"
#include "output.hpp"

namespace test {

    template <typename T>
    auto unit(const char* name, T&& function) noexcept -> int {
        const auto scope = aux::output(name);
        const auto registry = aux::registry();
        try {
            function();
        } catch (...) {
            aux::registry::on_exception(name);
        }
        return 0;
    }

}

#endif
