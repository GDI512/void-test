#include "common.hpp"

#include <forward_list>
#include <type_traits>
#include <vector>

int main() {
    {
        static_assert(std::is_same_v<int, typename test::remove_reference<int>::type>);
        static_assert(std::is_same_v<int, typename test::remove_reference<int&>::type>);
        static_assert(std::is_same_v<int, typename test::remove_reference<int&&>::type>);
    }
    {
        static_assert(test::is_lvalue_reference<int&>::value);
        static_assert(!test::is_lvalue_reference<int>::value);
        static_assert(!test::is_lvalue_reference<int&&>::value);
    }
    {
        auto value = 4;
        auto rvalue = [](int x) -> int { return x; };
        auto lvalue = [](int& x) -> int& { return x; };
        static_assert(std::is_same_v<int&&, decltype(test::cpp::forward<int>(lvalue(value)))>);
        static_assert(std::is_same_v<int&&, decltype(test::cpp::forward<int>(rvalue(value)))>);
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
        cassert(test::cpp::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::cpp::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 1, 3, 4, 5};
        cassert(test::cpp::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }));
        cassert(!test::cpp::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::cpp::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        cassert(!test::cpp::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!test::cpp::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }));
        cassert(!test::cpp::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
        cassert(test::cpp::all_of(list.begin(), list.end(), [](auto x){ return x < 6; }));
        cassert(!test::cpp::all_of(list.begin(), list.end(), [](auto x){ return x < 5; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        auto other = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        cassert(test::cpp::equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        auto other = std::forward_list<int>{0, 1, 1, 3, 4, 5};
        cassert(!test::cpp::equal(list.begin(), list.end(), other.begin()));
    }
}
