#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace void_test::core {

    constexpr auto exit_success = 0;
    constexpr auto exit_failure = 1;
    constexpr auto test_capacity = 64;

    class scope : public static_list<scope> {
      private:
        string name;

      public:
        ~scope() = default;
        scope(string name) noexcept;

      public:
        static auto data() noexcept -> string;
    };

    class registry : public static_list<registry> {
      public:
        struct state {
            size_type error_count;
            size_type success_count;
        };

      private:
        state info;

      public:
        ~registry() noexcept;
        registry() noexcept;

      public:
        static auto data() noexcept -> state;
        static auto empty() noexcept -> bool;
        static auto status() noexcept -> bool;
        static auto on_error(string source = "") noexcept -> size_type;
        static auto on_success(string source = "") noexcept -> size_type;
        static auto on_exception(string source = "") noexcept -> size_type;
    };

    class verifier : public static_list<verifier> {
      public:
        struct state {
            size_type destroyed_count;
            size_type constructed_count;
            size_type destructor_error_count;
            size_type constructor_error_count;
            size_type operator_error_count;
        };

      private:
        state info;

      public:
        ~verifier() noexcept;
        verifier() noexcept;

      public:
        static auto data() noexcept -> state;
        static auto empty() noexcept -> bool;
        static auto status() noexcept -> bool;
        static auto on_destruction() noexcept -> size_type;
        static auto on_construction() noexcept -> size_type;
        static auto on_destructor_error() noexcept -> size_type;
        static auto on_constructor_error() noexcept -> size_type;
        static auto on_operator_error() noexcept -> size_type;
    };

    class global {
      public:
        struct state {
            size_type error_count;
            size_type success_count;
        };

      private:
        static int exit_code;
        static size_type assert_error_count;
        static size_type assert_success_count;

      public:
        ~global() noexcept;
        global() noexcept;

      public:
        static auto exit_status() noexcept -> int;
        static auto exit_status(int code) noexcept -> void;
    };

    extern template class static_list<scope>;
    extern template class static_list<registry>;
    extern template class static_list<verifier>;

}

#endif
