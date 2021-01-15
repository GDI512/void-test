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

    template <typename result, typename... args>
    class callable_base {
      public:
        virtual ~callable_base() = default;

      public:
        virtual auto operator()(args... arguments) -> result = 0;
    };

    template <typename type, typename result, typename... args>
    class callable : callable_base<result, args...> {
      private:
        type functor;

      public:
        callable(type functor) : functor(functor) {}

      public:
        auto operator()(args... arguments) -> result override {
            return functor(forward<args>(arguments)...);
        }
    };

    template <typename type>
    class function;

    template <typename result, typename... args>
    class function<result(args...)> {
      private:
        alignas(16) byte buffer[32];

      public:
        template <typename type>
        function(type functor) {
            using invocable = callable<type, result, args...>;
            new (buffer) invocable(functor);
        }

      public:
        template <typename... argv>
        auto operator()(argv&&... arguments) -> result {
            using invocable_base = callable_base<result, args...>;
            return reinterpret_cast<invocable_base&>(*buffer)(forward<argv>(arguments)...);
        }
    };

}

#endif
