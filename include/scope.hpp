#ifndef VOID_TEST_SCOPE_HPP
#define VOID_TEST_SCOPE_HPP

#include "utility.hpp"

namespace void_test::core {

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

    extern template class static_list<scope>;

}

#endif
