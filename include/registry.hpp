#ifndef VOID_TEST_REGISTRY_HPP
#define VOID_TEST_REGISTRY_HPP

#include "state.hpp"
#include "utility.hpp"

namespace void_test::core {

    class registry : public static_list<registry> {
      public:
        struct state {
            size_type error_count;
            size_type success_count;
        };

      private:
        state test;

      public:
        ~registry() noexcept;
        registry() noexcept;

      public:
        static auto data() noexcept -> state;
        static auto empty() noexcept -> bool;
        static auto status() noexcept -> bool;
        static auto on_error(string source = "") noexcept -> size_type;
        static auto on_success(string source = "") noexcept -> size_type;
    };

    extern template class static_list<registry>;

}

#endif
