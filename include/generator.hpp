#ifndef VOID_TEST_GENERATOR_HPP
#define VOID_TEST_GENERATOR_HPP

#include "utility.hpp"

namespace test {

    template <typename T>
    class array {
      public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

      private:
        pointer buffer;
        size_type buffer_size;

      public:
        ~array() noexcept;
        array() noexcept;
        array(size_type size, value_type value = 0);
        array(const_iterator first, const_iterator last);
        array(array&& other) noexcept;
        array(const array& other);

      public:
        auto operator=(array&& other) noexcept -> array&;
        auto operator=(const array& other) -> array&;
        auto operator[](size_type index) noexcept -> reference;
        auto operator[](size_type index) const noexcept -> const_reference;

      public:
        auto swap(array& other) noexcept -> void;

      public:
        auto data() noexcept -> pointer;
        auto data() const noexcept -> pointer;
        auto front() noexcept -> reference;
        auto front() const noexcept -> const_reference;
        auto back() noexcept -> reference;
        auto back() const noexcept -> const_reference;
        auto begin() noexcept -> iterator;
        auto begin() const noexcept -> const_iterator;
        auto end() noexcept -> iterator;
        auto end() const noexcept -> const_iterator;
        auto empty() const noexcept -> bool;
        auto size() const noexcept -> size_type;
        auto capacity() const noexcept -> size_type;

      public:
        static auto random(size_type size, int min, int max) -> array<int>;
        static auto random(size_type size, float min, float max) -> array<float>;

        template <typename U>
        friend auto swap(array<U>& left, array<U>& right) noexcept -> void;
    };

    template <typename T>
    class generator {
      public:
        using value_type = T;

      public:
        struct impl;
        impl* pimpl;

      public:
        ~generator() noexcept;
        generator();
        generator(generator&& other) noexcept;
        generator(const generator& other) = delete;

      public:
        auto operator()() noexcept -> T;
        auto operator=(generator&& other) noexcept -> generator&;
        auto operator=(const generator& other) -> generator& = delete;

      public:
        auto swap(generator& other) noexcept -> void;

        template <typename U>
        friend auto swap(generator<U>& left, generator<U>& right) noexcept -> void;
    };

    template <typename T>
    auto swap(array<T>& left, array<T>& right) noexcept -> void;

    template <typename T>
    auto swap(generator<T>& left, generator<T>& right) noexcept -> void;

    extern template class array<int>;
    extern template class array<float>;
    extern template class generator<int>;
    extern template class generator<float>;

    extern template auto swap(array<int>&, array<int>&) noexcept -> void;
    extern template auto swap(array<float>&, array<float>&) noexcept -> void;
    extern template auto swap(generator<int>&, generator<int>&) noexcept -> void;
    extern template auto swap(generator<float>&, generator<float>&) noexcept -> void;

}

#endif
