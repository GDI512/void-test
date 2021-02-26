#include "common.hpp"

#include <type_traits>
#include <vector>

int main() {
    {
        static_assert(std::is_same<int, typename test::traits::remove_reference<int>::type>::value);
        static_assert(std::is_same<int, typename test::traits::remove_reference<int&>::type>::value);
        static_assert(std::is_same<int, typename test::traits::remove_reference<int&&>::type>::value);
    }
    {
        static_assert(test::traits::is_lvalue_reference<int&>::value);
        static_assert(!test::traits::is_lvalue_reference<int>::value);
        static_assert(!test::traits::is_lvalue_reference<int&&>::value);
    }
    {
        struct type {};
        static_assert(test::traits::is_same<int, int>::value);
        static_assert(test::traits::is_same<type, type>::value);
        static_assert(!test::traits::is_same<int, float>::value);
        static_assert(!test::traits::is_same<type&&, type>::value);
    }
    {
        struct type {};
        auto value = type{};
        static_assert(std::is_same<type&&, decltype(test::move(type{}))>::value);
        static_assert(std::is_same<type&&, decltype(test::move(value))>::value);
    }
    {
        auto value = 4;
        auto rvalue = [](int x) -> int { return x; };
        auto lvalue = [](int& x) -> int& { return x; };
        static_assert(std::is_same<int&&, decltype(test::forward<int>(lvalue(value)))>::value);
        static_assert(std::is_same<int&&, decltype(test::forward<int>(rvalue(value)))>::value);
    }
    {
        auto value = 4;
        auto other = 8;
        value = test::exchange(other, 0);
        CASSERT(value == 8);
        CASSERT(other == 0);
    }
    {
        int array[16] = {};
        auto vector = std::vector<int>(16);
        CASSERT(test::begin(array) == array);
        CASSERT(test::end(array) == array + 16);
        CASSERT(test::begin(vector) == vector.begin());
        CASSERT(test::end(vector) == vector.end());
    }
}
