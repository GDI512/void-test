#ifndef CPPLTF_OUTPUT_HPP
#define CPPLTF_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test::core {

    class output {
      public:
        static size_type indentation;

      public:
        ~output() noexcept;
        output(string name) noexcept;
        output(output&& other) = delete;
        output(const output& other) = delete;

      public:
        auto operator=(output&& other) -> output& = delete;
        auto operator=(const output& other) -> output& = delete;

      public:
        static auto on_error(string source) noexcept -> void;
        static auto on_success(string source) noexcept -> void;
        static auto on_exception(string source) noexcept -> void;
        static auto on_unit_error(state state) noexcept -> void;
        static auto on_unit_success(state state) noexcept -> void;
    };

}

#endif
