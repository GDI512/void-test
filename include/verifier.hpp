#ifndef VOID_TEST_VERIFIER_HPP
#define VOID_TEST_VERIFIER_HPP

#include "utility.hpp"

namespace void_test::core {

    class verifier : public static_list<verifier> {
      public:
        struct state {
            size_type destroyed;
            size_type constructed;
            size_type destructor_errrors;
            size_type constructor_errors;
            size_type operator_errors;
        };

      private:
        state count;

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

    extern template class static_list<verifier>;

}

#endif
