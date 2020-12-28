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

      public:
        static auto on_scope(string name) noexcept -> void;
        static auto on_error(string source) noexcept -> void;
        static auto on_success(string source) noexcept -> void;
        static auto on_exception(string source) noexcept -> void;
        static auto on_test_registry_error(test_registry::state data) noexcept -> void;
        static auto on_test_registry_success(test_registry::state data) noexcept -> void;
        static auto on_resource_verifier_error(resource_verifier::state data) noexcept -> void;
        static auto on_resource_verifier_success(resource_verifier::state data) noexcept -> void;
    };

}

#endif
