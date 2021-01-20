#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace test::core {

    constexpr auto exit_success = 0;
    constexpr auto exit_failure = 1;

    struct registry_state {
        size_type error_count;
        size_type success_count;
    };

    struct verifier_state {
        size_type destroyed_count;
        size_type constructed_count;
        size_type destructor_error_count;
        size_type constructor_error_count;
        size_type operator_error_count;
    };

    class scope : public static_list<scope> {
      private:
        string name;

      public:
        ~scope() = default;
        scope(string name) noexcept;
        scope(scope&& other) = delete;
        scope(const scope& other) = delete;

      public:
        auto operator=(scope&& other) -> scope& = delete;
        auto operator=(const scope& other) -> scope& = delete;

      public:
        static auto data() noexcept -> string;
    };

    class registry : public static_list<registry> {
      private:
        size_type error_count = 0;
        size_type success_count = 0;

      public:
        ~registry() noexcept;
        registry() noexcept;
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;

      public:
        static auto data() noexcept -> registry_state;
        static auto empty() noexcept -> bool;
        static auto status() noexcept -> bool;
        static auto on_error(string source = "") noexcept -> size_type;
        static auto on_success(string source = "") noexcept -> size_type;
        static auto on_exception(string source = "") noexcept -> size_type;
    };

    class verifier : public static_list<verifier> {
      private:
        atomic_counter destroyed_count = 0;
        atomic_counter constructed_count = 0;
        atomic_counter destructor_error_count = 0;
        atomic_counter constructor_error_count = 0;
        atomic_counter operator_error_count = 0;

      public:
        ~verifier() noexcept;
        verifier() noexcept;
        verifier(verifier&& other) = delete;
        verifier(const verifier& other) = delete;

      public:
        auto operator=(verifier&& other) -> verifier& = delete;
        auto operator=(const verifier& other) -> verifier& = delete;

      public:
        static auto data() noexcept -> verifier_state;
        static auto empty() noexcept -> bool;
        static auto status() noexcept -> bool;
        static auto on_destruction() noexcept -> size_type;
        static auto on_construction() noexcept -> size_type;
        static auto on_destructor_error() noexcept -> size_type;
        static auto on_constructor_error() noexcept -> size_type;
        static auto on_operator_error() noexcept -> size_type;
    };

    class global {
      private:
        static int exit_code;

      public:
        static auto exit_status() noexcept -> int;
        static auto exit_status(int code) noexcept -> void;
    };

    extern template class static_list<scope>;
    extern template class static_list<registry>;
    extern template class static_list<verifier>;

}

#endif
