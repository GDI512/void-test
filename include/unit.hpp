#ifndef VOID_TEST_UNIT_HPP
#define VOID_TEST_UNIT_HPP

#include "state.hpp"
#include "output.hpp"
#include "utility.hpp"

namespace test {

    template <typename T>
    auto unit(const char* name, T&& function) noexcept -> int {
        auto scope = core::scope(name);
        auto registry = core::registry();
        auto verifier = core::verifier();
        try {
            function();
        } catch (...) {
            core::on_exception(name);
        }
        return 0;
    }

}

#endif
