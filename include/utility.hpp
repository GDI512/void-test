#ifndef VOID_TEST_UTILITY_HPP
#define VOID_TEST_UTILITY_HPP

namespace void_test {

    using string = const char*;
    using size_type = unsigned int;

}

namespace void_test::core {

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
    constexpr auto forward(typename remove_reference<T>::type& value) noexcept -> T&& {
        return static_cast<T&&>(value);
    }

    template <typename T>
    constexpr auto forward(typename remove_reference<T>::type&& value) noexcept -> T&& {
        static_assert(!is_lvalue_reference<T>::value);
        return static_cast<T&&>(value);
    }

    template <typename T>
    class static_list {
      private:
        static static_list* active_node;

      private:
        static_list* previous_node;

      public:
        ~static_list() noexcept;
        static_list() noexcept;

      public:
        static auto current() noexcept -> T&;
        static auto is_linked() noexcept -> bool;
    };

}

#endif
