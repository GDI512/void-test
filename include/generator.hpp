#ifndef VOID_TEST_GENERATOR_HPP
#define VOID_TEST_GENERATOR_HPP

#include "utility.hpp"

namespace test {

    template <typename T>
    class range {
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
        ~range() noexcept;
        range() noexcept;
        range(size_type size, value_type value = 0);
        range(const_iterator first, const_iterator last);
        range(range&& other) noexcept;
        range(const range& other);

      public:
        auto operator=(range&& other) noexcept -> range&;
        auto operator=(const range& other) -> range&;
        auto operator[](size_type index) noexcept -> reference;
        auto operator[](size_type index) const noexcept -> const_reference;

      public:
        auto swap(range& other) noexcept -> void;

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
        static auto random(size_type size, value_type min, value_type max) -> range;
        static auto sequence(size_type size, value_type start, value_type step) -> range;

        template <typename U>
        friend auto swap(range<U>& left, range<U>& right) noexcept -> void;
    };

    template <typename T>
    class generator {};

    template <>
    class generator<float> {
      private:
        static generator instance;

      private:
        struct impl;
        impl* pimpl;

      public:
        ~generator() noexcept;
        generator() noexcept;
        generator(generator&& other) = delete;
        generator(const generator& other) = delete;

      public:
        auto operator()() -> float;
        auto operator=(generator&& other) -> generator& = delete;
        auto operator=(const generator& other) -> generator& = delete;

      public:
        static auto get() -> float;
    };

    template <>
    class generator<int> {
      private:
        static generator instance;

      private:
        struct impl;
        impl* pimpl;

      public:
        ~generator() noexcept;
        generator() noexcept;
        generator(generator&& other) = delete;
        generator(const generator& other) = delete;

      public:
        auto operator()() -> int;
        auto operator=(generator&& other) -> generator& = delete;
        auto operator=(const generator& other) -> generator& = delete;

      public:
        static auto get() -> int;
    };

    template <typename T>
    auto swap(range<T>& left, range<T>& right) noexcept -> void;

    extern template class range<int>;
    extern template class range<float>;
    extern template class generator<int>;
    extern template class generator<float>;

    extern template auto swap(range<int>&, range<int>&) noexcept -> void;
    extern template auto swap(range<float>&, range<float>&) noexcept -> void;

}

#endif
