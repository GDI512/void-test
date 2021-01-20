#ifndef VOID_TEST_UTILITY_HPP
#define VOID_TEST_UTILITY_HPP

namespace void_test {

    using byte = unsigned char;
    using string = const char*;
    using size_type = int;

}

namespace void_test::core {

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
    constexpr auto forward(typename remove_reference<type>::type& value) noexcept -> type&& {
        return static_cast<type&&>(value);
    }

    template <typename type>
    constexpr auto forward(typename remove_reference<type>::type&& value) noexcept -> type&& {
        static_assert(!is_lvalue_reference<type>::value);
        return static_cast<type&&>(value);
    }

    template <typename type>
    class static_list {
      private:
        static static_list* active;

      private:
        static_list* previous;

      public:
        ~static_list() noexcept;
        static_list() noexcept;
        static_list(static_list&& other) = delete;
        static_list(const static_list& other) = delete;

      public:
        auto operator=(static_list&& other) -> static_list& = delete;
        auto operator=(const static_list& other) -> static_list& = delete;

      public:
        static auto current() noexcept -> type&;
    };

    class atomic_counter {
      private:
        struct impl;
        impl* pimpl;

      public:
        ~atomic_counter();
        atomic_counter();
        atomic_counter(atomic_counter&& other) = delete;
        atomic_counter(const atomic_counter& other) = delete;

      public:
        operator int() const noexcept;
        auto operator++(int) noexcept -> int;
        auto operator--(int) noexcept -> int;
        auto operator=(atomic_counter&& other) -> atomic_counter& = delete;
        auto operator=(const atomic_counter& other) -> atomic_counter& = delete;
    };

}

#endif
