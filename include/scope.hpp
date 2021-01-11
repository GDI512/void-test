#ifndef VOID_TEST_SCOPE_HPP
#define VOID_TEST_SCOPE_HPP

#include "state.hpp"
#include "utility.hpp"

namespace void_test::core {

    class scope : public static_list<scope> {
      private:
        string name;

      public:
        ~scope() = default;
        scope(string name) noexcept;

      public:
        static auto data() noexcept -> string;
    };

    extern template class static_list<scope>;

}

#endif
