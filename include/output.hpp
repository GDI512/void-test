#ifndef VOID_TEST_OUTPUT_HPP
#define VOID_TEST_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test::core {

    class output {
      private:
        static size_type indent_level;

      public:
        ~output() noexcept;
        output() noexcept;
        output(output&& other) = delete;
        output(const output& other) = delete;

      public:
        auto operator=(output&& other) -> output& = delete;
        auto operator=(const output& other) -> output& = delete;

      public:
        static auto on_scope(string name) noexcept -> void;
        static auto on_error(string source) noexcept -> void;
        static auto on_success(string source) noexcept -> void;
        static auto on_exception(string source) noexcept -> void;
        static auto on_test_error(registry_state data) noexcept -> void;
        static auto on_test_success(registry_state data) noexcept -> void;
        static auto on_resource_error(verifier_state data) noexcept -> void;
        static auto on_resource_success(verifier_state data) noexcept -> void;
    };

}

#endif
