#ifndef CPPLTF_OUTPUT_HPP
#define CPPLTF_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test {

    extern size_type indent_level;

    class scope {
      public:
        ~scope() noexcept;
        scope(const char* name) noexcept;
        scope(scope&& other) = delete;
        scope(const scope& other) = delete;

      public:
        auto operator=(scope&& other) -> scope& = delete;
        auto operator=(const scope& other) -> scope& = delete;

      public:
        static auto on_error(const char* source) noexcept -> void;
        static auto on_success(const char* source) noexcept -> void;
        static auto on_exception(const char* source) noexcept -> void;
        static auto on_registry_error(test_info state) noexcept -> void;
        static auto on_registry_success(test_info state) noexcept -> void;
        static auto on_verifier_error(object_info state) noexcept -> void;
        static auto on_verifier_success(object_info state) noexcept -> void;
    };

}

#endif
