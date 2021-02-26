#include "common.hpp"

#include <type_traits>
#include <vector>

using namespace test;

int main() {
    {
        static_assert(std::is_same<int, core::remove_reference<int>>::value);
        static_assert(std::is_same<int, core::remove_reference<int&>>::value);
        static_assert(std::is_same<int, core::remove_reference<int&&>>::value);
    }
    {
        static_assert(core::is_lvalue_reference<int&>);
        static_assert(!core::is_lvalue_reference<int>);
        static_assert(!core::is_lvalue_reference<int&&>);
    }
    {
        struct type {};
        static_assert(core::is_same<int, int>);
        static_assert(core::is_same<type, type>);
        static_assert(!core::is_same<int, float>);
        static_assert(!core::is_same<type&&, type>);
    }
    {
        struct type {};
        auto value = type{};
        static_assert(std::is_same<type&&, decltype(core::move(type{}))>::value);
        static_assert(std::is_same<type&&, decltype(core::move(value))>::value);
    }
    {
        auto value = 4;
        auto rvalue = [](int x) -> int { return x; };
        auto lvalue = [](int& x) -> int& { return x; };
        static_assert(std::is_same<int&&, decltype(core::forward<int>(lvalue(value)))>::value);
        static_assert(std::is_same<int&&, decltype(core::forward<int>(rvalue(value)))>::value);
    }
    {
        auto value = 4;
        auto other = 8;
        value = core::exchange(other, 0);
        CASSERT(value == 8);
        CASSERT(other == 0);
    }
    {
        int array[16] = {};
        auto vector = std::vector<int>(16);
        CASSERT(core::begin(array) == array);
        CASSERT(core::end(array) == array + 16);
        CASSERT(core::begin(vector) == vector.begin());
        CASSERT(core::end(vector) == vector.end());
    }
}
