#ifndef VOID_TEST_OUTPUT_HPP
#define VOID_TEST_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test::core {

    class output {
      private:
        static size_type indent;

      public:
        ~output() noexcept;
        output() noexcept;

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
