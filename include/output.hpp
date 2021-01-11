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

      public:
        static auto on_scope(string name) noexcept -> void;
        static auto on_error(string source) noexcept -> void;
        static auto on_success(string source) noexcept -> void;
        static auto on_exception(string source) noexcept -> void;
        static auto on_test_error(registry::state data) noexcept -> void;
        static auto on_test_success(registry::state data) noexcept -> void;
        static auto on_resource_error(verifier::state data) noexcept -> void;
        static auto on_resource_success(verifier::state data) noexcept -> void;
    };

}

#endif
