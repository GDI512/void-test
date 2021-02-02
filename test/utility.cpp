#include "common.hpp"

#include <vector>
#include <utility>
#include <type_traits>

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
        auto value = 4;
        auto rvalue = [](int x) -> int { return x; };
        auto lvalue = [](int& x) -> int& { return x; };
        static_assert(std::is_same<int&&, decltype(core::forward<int>(lvalue(value)))>::value);
        static_assert(std::is_same<int&&, decltype(core::forward<int>(rvalue(value)))>::value);
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
