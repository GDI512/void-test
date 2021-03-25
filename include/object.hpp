#ifndef CPPLTF_TYPE_HPP
#define CPPLTF_TYPE_HPP

#include "utility.hpp"

namespace test {

    class object {
      private:
        volatile object* self;
        volatile integer value;
        volatile integer number;

      public:
        ~object() noexcept;
        object(integer number = 0) noexcept;
        object(object&& other) noexcept;
        object(const object& other) noexcept;

      public:
        operator integer() const noexcept;
        auto operator=(object&& other) noexcept -> object&;
        auto operator=(const object& other) noexcept -> object&;

      private:
        auto is_self() const noexcept -> bool;
        auto is_initialized() const noexcept -> bool;
        auto is_uninitialized() const noexcept -> bool;
    };

    class counter {
      private:
        integer number;

      public:
        ~counter() noexcept;
        counter(integer number = 0) noexcept;
        counter(counter&& other) noexcept;
        counter(const counter& other) noexcept;

      public:
        operator integer() const noexcept;
        auto operator=(counter&& other) noexcept -> counter&;
        auto operator=(const counter& other) noexcept -> counter&;
    };

}

#endif
