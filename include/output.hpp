#ifndef VOID_TEST_OUTPUT_HPP
#define VOID_TEST_OUTPUT_HPP

#include "utility.hpp"
#include "verifier.hpp"
#include "registry.hpp"

namespace void_test::core {

    class output {
      private:
        static size_type indent_level;

      public:
        ~output() noexcept;
        output() noexcept;
        output(output&& other) = delete;
        output(const output& other) = delete;

      public:
        auto operator=(output&& other) = delete;
        auto operator=(const output& other) = delete;

      public:
        static auto on_scope(string name) noexcept -> void;
        static auto on_error(string source) noexcept -> void;
        static auto on_success(string source) noexcept -> void;
        static auto on_exception(string source) noexcept -> void;
        static auto on_registry_error(registry::state data) noexcept -> void;
        static auto on_registry_success(registry::state data) noexcept -> void;
        static auto on_verifier_error(verifier::state data) noexcept -> void;
        static auto on_verifier_success(verifier::state data) noexcept -> void;
    };

}

#endif
