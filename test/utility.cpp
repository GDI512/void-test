#include "common.hpp"

using namespace test;

int main() {
    {
        static_assert(std::is_same<int, core::remove_reference<int>::type>::value);
        static_assert(std::is_same<int, core::remove_reference<int&>::type>::value);
        static_assert(std::is_same<int, core::remove_reference<int&&>::type>::value);
    }
    {
        static_assert(core::is_lvalue_reference<int&>::value);
        static_assert(!core::is_lvalue_reference<int>::value);
        static_assert(!core::is_lvalue_reference<int&&>::value);
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
        cassert(value == 8);
        cassert(other == 0);
    }
    {
        int array[16] = {};
        auto vector = std::vector<int>(16);
        cassert(core::begin(array) == array);
        cassert(core::end(array) == array + 16);
        cassert(core::begin(vector) == vector.begin());
        cassert(core::end(vector) == vector.end());
    }
}
