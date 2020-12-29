#ifndef VOID_TEST_VERIFIER_HPP
#define VOID_TEST_VERIFIER_HPP

#include "utility.hpp"

namespace void_test::core {

    class verifier : public static_list<verifier> {
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
        ~verifier() noexcept;
        verifier() noexcept;
        verifier(verifier&& other) = delete;
        verifier(const verifier& other) = delete;

      public:
        auto operator=(verifier&& other) -> verifier& = delete;
        auto operator=(const verifier& other) -> verifier& = delete;

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

    extern template class static_list<verifier>;

}

#endif
