#ifndef VOID_TEST_UTILITY_HPP
#define VOID_TEST_UTILITY_HPP

namespace test {

    using size_t = unsigned long long;
    using ptrdiff_t = long long;

}

namespace test::core {

    struct true_type {
        static constexpr auto value = true;
    };

    struct false_type {
        static constexpr auto value = false;
    };

    template <typename T>
    struct remove_reference {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&> {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&> {
        using type = T;
    };

    template <typename T>
    struct is_lvalue_reference : false_type {};

    template <typename T>
    struct is_lvalue_reference<T&> : true_type {};

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    template <typename T>
    constexpr auto is_lvalue_reference_v = is_lvalue_reference<T>::value;

    template <typename T>
    constexpr auto move(T&& value) noexcept -> remove_reference_t<T>&& {
        return static_cast<remove_reference_t<T>&&>(value);
    }

    template <typename T>
    constexpr auto forward(remove_reference_t<T>& value) noexcept -> T&& {
        return static_cast<T&&>(value);
    }

    template <typename T>
    constexpr auto forward(remove_reference_t<T>&& value) noexcept -> T&& {
        static_assert(!is_lvalue_reference_v<T>);
        return static_cast<T&&>(value);
    }

    template <typename T, typename U>
    constexpr auto exchange(T& value, U&& new_value) -> T {
        auto old_value = move(value);
        value = forward<U>(new_value);
        return old_value;
    }

    template <typename T>
    constexpr auto begin(T& container) -> decltype(container.begin()) {
        return container.begin();
    }

    template <typename T>
    constexpr auto begin(const T& container) -> decltype(container.begin()) {
        return container.begin();
    }

    template <typename T, auto N>
    constexpr auto begin(T (&array)[N]) -> T* {
        return static_cast<T*>(array);
    }

    template <typename T, auto N>
    constexpr auto begin(const T (&array)[N]) -> const T* {
        return static_cast<const T*>(array);
    }

    template <typename T>
    constexpr auto end(T& container) -> decltype(container.end()) {
        return container.end();
    }

    template <typename T>
    constexpr auto end(const T& container) -> decltype(container.end()) {
        return container.end();
    }

    template <typename T, auto N>
    constexpr auto end(T (&array)[N]) -> T* {
        return array + N;
    }

    template <typename T, auto N>
    constexpr auto end(const T (&array)[N]) -> const T* {
        return array + N;
    }

}

#endif
