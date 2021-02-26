#ifndef CPPLTF_UNIT_HPP
#define CPPLTF_UNIT_HPP

#include "state.hpp"
#include "output.hpp"
#include "utility.hpp"

namespace test {

    template <typename T>
    auto unit(const char* name, T&& function) noexcept -> int {
        const auto scope = test::output(name);
        const auto registry = test::registry();
        try {
            function();
        } catch (...) {
            registry::on_exception(name);
        }
        return 0;
    }

}

#endif
