#include "common.hpp"

#include <forward_list>
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
        cassert(value == 8);
        cassert(other == 0);
    }
    {
        int array[16] = {};
        auto vector = std::vector<int>(16);
        cassert(test::begin(array) == array);
        cassert(test::begin(vector) == vector.begin());
    }
    {
        int array[16] = {};
        auto vector = std::vector<int>(16);
        cassert(test::end(array) == array + 16);
        cassert(test::end(vector) == vector.end());
    }
    {
        auto x = 10;
        auto y = test::exchange(x, 5);
        cassert(x == 5);
        cassert(y == 10);
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
        cassert(test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 1, 3, 4, 5};
        cassert(test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }));
        cassert(!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        cassert(!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }));
        cassert(!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
        cassert(test::all_of(list.begin(), list.end(), [](auto x){ return x < 6; }));
        cassert(!test::all_of(list.begin(), list.end(), [](auto x){ return x < 5; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        auto other = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        cassert(test::equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        auto other = std::forward_list<int>{0, 1, 1, 3, 4, 5};
        cassert(!test::equal(list.begin(), list.end(), other.begin()));
    }
}
