#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace test {

    constexpr auto exit_success = 0;
    constexpr auto exit_failure = 1;

    auto status() noexcept -> int;

}

namespace test::core {

    extern int exit_status;

    template <typename T>
    class auto_node {
      public:
        using pointer = auto_node*;
        using reference = T&;

      private:
        static pointer active;

      private:
        pointer previous;

      public:
        ~auto_node() noexcept;
        auto_node() noexcept;

      public:
        static auto current() noexcept -> reference;
    };

    class scope : public auto_node<scope> {
      public:
        using state = string;

      private:
        state info;

      public:
        scope(string info) noexcept;

      public:
        auto data() noexcept -> state;
    };

    class registry : public auto_node<registry> {
      public:
        struct state {
            size_type passed;
            size_type failed;
        };

      private:
        state info;

      public:
        ~registry() noexcept;
        registry() noexcept;

      public:
        auto data() const noexcept -> state;
        auto empty() const noexcept -> bool;
        auto status() const noexcept -> bool;

      public:
        static auto on_error() noexcept -> size_type;
        static auto on_success() noexcept -> size_type;
    };

    class verifier : public auto_node<verifier> {
      public:
        struct state {
            size_type destroyed;
            size_type constructed;
            size_type destructor_errors;
            size_type constructor_errors;
            size_type operator_errors;
        };

      private:
        state info;

      public:
        ~verifier() noexcept;
        verifier() noexcept;

      public:
        auto data() const noexcept -> state;
        auto empty() const noexcept -> bool;
        auto status() const noexcept -> bool;

      public:
        static auto on_destruction() noexcept -> size_type;
        static auto on_contruction() noexcept -> size_type;
        static auto on_destructor_error() noexcept -> size_type;
        static auto on_constructor_error() noexcept -> size_type;
        static auto on_operator_error() noexcept -> size_type;
    };

    extern template class auto_node<scope>;
    extern template class auto_node<registry>;
    extern template class auto_node<verifier>;

}

#endif
