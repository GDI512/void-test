#ifndef VOIDTEST_UTILITY_HPP
#define VOIDTEST_UTILITY_HPP

namespace test {

    using uint = unsigned int;
    using string = const char*;

}

namespace test::core {

    struct true_type {
        static constexpr auto value = true;
    };

    struct false_type {
        static constexpr auto value = false;
    };

    template <typename object_type>
    struct remove_reference {
        using type = object_type;
    };

    template <typename object_type>
    struct remove_reference<object_type&> {
        using type = object_type;
    };

    template <typename object_type>
    struct remove_reference<object_type&&> {
        using type = object_type;
    };

    template <typename object_type>
    struct is_lvalue_reference : false_type {};

    template <typename object_type>
    struct is_lvalue_reference<object_type&> : true_type {};

    template <typename type>
    using remove_reference_t = typename remove_reference<type>::type;

    template <typename type>
    constexpr auto is_lvalue_reference_v = is_lvalue_reference<type>::value;

    template <typename type>
    constexpr auto forward(remove_reference_t<type>& value) noexcept -> type&& {
        return static_cast<type&&>(value);
    }

    template <typename type>
    constexpr auto forward(remove_reference_t<type>&& value) noexcept -> type&& {
        static_assert(!is_lvalue_reference_v<type>);
        return static_cast<type&&>(value);
    }

}

#endif
