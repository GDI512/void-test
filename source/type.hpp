#ifndef CITRINE_TYPE_HPP
#define CITRINE_TYPE_HPP

#include "utility.hpp"

namespace citrine {

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

    template <typename T, auto N>
    class sequence {
      public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

      private:
        T array[N];

      public:
        sequence(value_type value = value_type(), const_reference step = value_type()) noexcept;

      public:
        constexpr auto fill(value_type value = value_type(), const_reference step = value_type()) noexcept -> void;

      public:
        constexpr auto begin() noexcept -> iterator;
        constexpr auto begin() const noexcept -> const_iterator;
        constexpr auto end() noexcept -> iterator;
        constexpr auto end() const noexcept -> const_iterator;
        constexpr auto size() const noexcept -> size_type;
        constexpr auto capacity() const noexcept -> size_type;
    };

    template <typename T, auto N>
    sequence<T, N>::sequence(value_type value, const_reference step) noexcept {
        fill(value, step);
    }

    template <typename T, auto N>
    constexpr auto sequence<T, N>::fill(value_type value, const_reference step) noexcept -> void {
        for (auto& item : array) {
            item = value;
            value += step;
        }
    }

    template <typename T, auto N>
    constexpr auto sequence<T, N>::begin() noexcept -> iterator {
        return array;
    }

    template <typename T, auto N>
    constexpr auto sequence<T, N>::begin() const noexcept -> const_iterator {
        return array;
    }

    template <typename T, auto N>
    constexpr auto sequence<T, N>::end() noexcept -> iterator {
        return array + size();
    }

    template <typename T, auto N>
    constexpr auto sequence<T, N>::end() const noexcept -> const_iterator {
        return array + size();
    }

    template <typename T, auto N>
    constexpr auto sequence<T, N>::size() const noexcept -> size_type {
        return capacity();
    }

    template <typename T, auto N>
    constexpr auto sequence<T, N>::capacity() const noexcept -> size_type {
        return N;
    }

}

#endif
