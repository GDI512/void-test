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
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;

      public:
        auto data() const noexcept -> state;
        auto empty() const noexcept -> bool;
        auto status() const noexcept -> bool;
        auto on_error() noexcept -> size_type;
        auto on_success() noexcept -> size_type;
    };

    extern template class static_list<registry>;

}

#endif
