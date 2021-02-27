#ifndef CPPLTF_OUTPUT_HPP
#define CPPLTF_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test::aux {

    class output {
      public:
        ~output() noexcept;
        output(const char* name) noexcept;
        output(output&& other) = delete;
        output(const output& other) = delete;

      public:
        auto operator=(output&& other) -> output& = delete;
        auto operator=(const output& other) -> output& = delete;

      public:
        static auto on_error(const char* source) noexcept -> void;
        static auto on_success(const char* source) noexcept -> void;
        static auto on_exception(const char* source) noexcept -> void;
        static auto on_unit_error(state state) noexcept -> void;
        static auto on_unit_success(state state) noexcept -> void;
    };

    extern size_type indentation;

}

#endif
