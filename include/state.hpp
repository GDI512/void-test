#ifndef CPPLTF_STATE_HPP
#define CPPLTF_STATE_HPP

#include "utility.hpp"

namespace test {

    enum class exit_code : int { success = 0, failure = 1, internal_error = 2 };

    struct test_info {
        size_type total_count;
        size_type error_count;
    };

    struct object_info {
        size_type destroyed_count;
        size_type constructed_count;
        size_type destructor_error_count;
        size_type constructor_error_count;
        size_type operator_error_count;
    };

    struct global_info {
        test_info test_state;
        object_info object_state;
    };

    class registry {
      private:
        test_info snapshot;

      public:
        ~registry() noexcept;
        registry() noexcept;
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;

      public:
        static auto on_error(const char* source) noexcept -> bool;
        static auto on_success(const char* source) noexcept -> bool;
        static auto on_exception(const char* source) noexcept -> void;
    };

    class verifier {
      private:
        object_info snapshot;

      public:
        ~verifier() noexcept;
        verifier() noexcept;
        verifier(verifier&& other) = delete;
        verifier(const verifier& other) = delete;

      public:
        auto operator=(verifier&& other) -> verifier& = delete;
        auto operator=(const verifier& other) -> verifier& = delete;

      public:
        static auto on_destruction() noexcept -> void;
        static auto on_construction() noexcept -> void;
        static auto on_destructor_error() noexcept -> void;
        static auto on_constructor_error() noexcept -> void;
        static auto on_operator_error() noexcept -> void;
    };

    auto restore_global_state(test_info result) noexcept -> void;
    auto restore_global_state(object_info result) noexcept -> void;

    auto compute_unit_result(test_info snapshot) noexcept -> test_info;
    auto compute_unit_result(object_info snapshot) noexcept -> object_info;

    auto empty(test_info state) noexcept -> bool;
    auto empty(object_info state) noexcept -> bool;

    auto error_free(test_info state) noexcept -> bool;
    auto error_free(object_info state) noexcept -> bool;

    extern exit_code code;
    extern global_info global;

}

#endif
