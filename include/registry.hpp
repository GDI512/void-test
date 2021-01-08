#ifndef VOID_TEST_REGISTRY_HPP
#define VOID_TEST_REGISTRY_HPP

#include "utility.hpp"

namespace void_test::core {

    class registry : public static_list<registry> {
      public:
        struct state {
            size_type passed;
            size_type failed;
        };

      private:
        state count;

      public:
        ~registry() noexcept;
        registry() noexcept;

      public:
        static auto data() noexcept -> state;
        static auto empty() noexcept -> bool;
        static auto status() noexcept -> bool;
        static auto on_error() noexcept -> size_type;
        static auto on_success() noexcept -> size_type;
    };

    extern template class static_list<registry>;

}

#endif
