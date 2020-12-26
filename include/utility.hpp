#ifndef VOID_TEST_UTILITY_HPP
#define VOID_TEST_UTILITY_HPP

namespace test {

    using string = const char*;
    using size_type = unsigned int;

}

namespace test::core {

    namespace impl {

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

    }

    template <typename T>
    using remove_reference = typename impl::remove_reference<T>::type;

    template <typename T>
    constexpr auto is_lvalue_reference = impl::is_lvalue_reference<T>::value;

    template <typename T>
    constexpr auto forward(remove_reference<T>& value) noexcept -> T&& {
        return static_cast<T&&>(value);
    }

    template <typename T>
    constexpr auto forward(remove_reference<T>&& value) noexcept -> T&& {
        static_assert(!is_lvalue_reference<T>);
        return static_cast<T&&>(value);
    }

}

#endif
