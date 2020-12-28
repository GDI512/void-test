#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace test {

    constexpr auto exit_success = 0;
    constexpr auto exit_failure = 1;

    auto exit_status() noexcept -> int;

}

namespace test::core {

    extern int exit_status;

    template <typename T>
    class static_list {
      public:
        using pointer = static_list*;
        using reference = T&;

      private:
        static pointer active_node;

      private:
        pointer previous_node;

      public:
        ~static_list() noexcept;
        static_list() noexcept;

      public:
        static auto current() noexcept -> reference;
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
        auto data() noexcept -> string;
    };

    class test_registry : public static_list<test_registry> {
      public:
        struct state {
            size_type passed;
            size_type failed;
        };

      private:
        state count;

      public:
        ~test_registry() noexcept;
        test_registry() noexcept;
        test_registry(test_registry&& other) = delete;
        test_registry(const test_registry& other) = delete;

      public:
        auto operator=(test_registry&& other) -> test_registry& = delete;
        auto operator=(const test_registry& other) -> test_registry& = delete;

      public:
        auto data() const noexcept -> state;
        auto empty() const noexcept -> bool;
        auto status() const noexcept -> bool;
        auto on_error() noexcept -> size_type;
        auto on_success() noexcept -> size_type;
    };

    class resource_verifier : public static_list<resource_verifier> {
      public:
        struct state {
            size_type destroyed;
            size_type constructed;
            size_type destructor_errors;
            size_type constructor_errors;
            size_type operator_errors;
        };

      private:
        state count;

      public:
        ~resource_verifier() noexcept;
        resource_verifier() noexcept;
        resource_verifier(resource_verifier&& other) = delete;
        resource_verifier(const resource_verifier& other) = delete;

      public:
        auto operator=(resource_verifier&& other) -> resource_verifier& = delete;
        auto operator=(const resource_verifier& other) -> resource_verifier& = delete;

      public:
        auto data() const noexcept -> state;
        auto empty() const noexcept -> bool;
        auto status() const noexcept -> bool;
        auto on_destruction() noexcept -> size_type;
        auto on_construction() noexcept -> size_type;
        auto on_destructor_error() noexcept -> size_type;
        auto on_constructor_error() noexcept -> size_type;
        auto on_operator_error() noexcept -> size_type;
    };

    extern template class static_list<scope>;
    extern template class static_list<test_registry>;
    extern template class static_list<resource_verifier>;

}

#endif
