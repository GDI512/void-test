#ifndef CPPLTF_TYPE_TRAITS_HPP
#define CPPLTF_TYPE_TRAITS_HPP

namespace test::traits {

    struct true_type {
        static constexpr auto value = true;
    };

    struct false_type {
        static constexpr auto value = false;
    };

    struct size_type {
        using type = decltype(sizeof(unsigned));
    };

    struct difference_type {
        using type = decltype(static_cast<unsigned*>(0) - static_cast<unsigned*>(0));
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

    template <typename T, typename U>
    struct is_same : false_type {};

    template <typename T>
    struct is_same<T, T> : true_type {};

    template <typename T>
    struct is_lvalue_reference : false_type {};

    template <typename T>
    struct is_lvalue_reference<T&> : true_type {};

}

#endif
