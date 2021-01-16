#ifndef VOID_TEST_UTILITY_HPP
#define VOID_TEST_UTILITY_HPP

namespace void_test {

    using byte = unsigned char;
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

    template <typename T>
    class static_list {
      private:
        inline static static_list* active_node = nullptr;

      private:
        static_list* previous_node;

      public:
        ~static_list() noexcept {
            active_node = previous_node;
        }
        static_list() noexcept {
            previous_node = active_node;
            active_node = this;
        }

      public:
        static auto current() noexcept -> T& {
            return static_cast<T&>(*active_node);
        }
    };

}

#endif
