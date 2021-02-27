#include "common.hpp"

#include <forward_list>
#include <type_traits>
#include <vector>

int main() {
    {
        static_assert(std::is_same<int, typename test::aux::remove_reference<int>::type>::value);
        static_assert(std::is_same<int, typename test::aux::remove_reference<int&>::type>::value);
        static_assert(std::is_same<int, typename test::aux::remove_reference<int&&>::type>::value);
    }
    {
        static_assert(test::aux::is_lvalue_reference<int&>::value);
        static_assert(!test::aux::is_lvalue_reference<int>::value);
        static_assert(!test::aux::is_lvalue_reference<int&&>::value);
    }
    {
        struct type {};
        static_assert(test::aux::is_same<int, int>::value);
        static_assert(test::aux::is_same<type, type>::value);
        static_assert(!test::aux::is_same<int, float>::value);
        static_assert(!test::aux::is_same<type&&, type>::value);
    }
    {
        struct type {};
        auto value = type{};
        static_assert(std::is_same<type&&, decltype(test::aux::move(type{}))>::value);
        static_assert(std::is_same<type&&, decltype(test::aux::move(value))>::value);
    }
    {
        auto value = 4;
        auto rvalue = [](int x) -> int { return x; };
        auto lvalue = [](int& x) -> int& { return x; };
        static_assert(std::is_same<int&&, decltype(test::aux::forward<int>(lvalue(value)))>::value);
        static_assert(std::is_same<int&&, decltype(test::aux::forward<int>(rvalue(value)))>::value);
    }
    {
        auto value = 4;
        auto other = 8;
        value = test::aux::exchange(other, 0);
        cassert(value == 8);
        cassert(other == 0);
    }
    {
        int array[16] = {};
        auto vector = std::vector<int>(16);
        cassert(test::aux::begin(array) == array);
        cassert(test::aux::begin(vector) == vector.begin());
    }
    {
        int array[16] = {};
        auto vector = std::vector<int>(16);
        cassert(test::aux::end(array) == array + 16);
        cassert(test::aux::end(vector) == vector.end());
    }
    {
        auto x = 10;
        auto y = test::aux::exchange(x, 5);
        cassert(x == 5);
        cassert(y == 10);
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
        cassert(test::aux::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::aux::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 1, 3, 4, 5};
        cassert(test::aux::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }));
        cassert(!test::aux::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::aux::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        cassert(!test::aux::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::aux::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }));
        cassert(!test::aux::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
        cassert(test::aux::all_of(list.begin(), list.end(), [](auto x){ return x < 6; }));
        cassert(!test::aux::all_of(list.begin(), list.end(), [](auto x){ return x < 5; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        auto other = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        cassert(test::aux::equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        auto other = std::forward_list<int>{0, 1, 1, 3, 4, 5};
        cassert(!test::aux::equal(list.begin(), list.end(), other.begin()));
    }
}
