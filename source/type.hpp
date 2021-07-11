#ifndef CITRINE_TYPE_HPP
#define CITRINE_TYPE_HPP

#include "utility.hpp"

namespace test {

    class counter {
      private:
        int value;

      public:
        ~counter() noexcept;
        counter(int value = 0) noexcept;
        counter(counter&& other) noexcept;
        counter(const counter& other) noexcept;

      public:
        operator int() const noexcept;
        auto operator=(counter&& other) noexcept -> counter&;
        auto operator=(const counter& other) noexcept -> counter&;
    };

}

#endif
