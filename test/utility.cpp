#include "common.hpp"

#include <forward_list>
#include <type_traits>
#include <utility>

int main() {
    {
        cassert((std::is_same_v<int, typename citrine::remove_reference<int>::type>));
        cassert((std::is_same_v<int, typename citrine::remove_reference<int&>::type>));
        cassert((std::is_same_v<int, typename citrine::remove_reference<int&&>::type>));
    }
    {
        auto value = 4;
        auto rexpr = [](int x) -> int { return x; };
        auto lexpr = [](int& x) -> int& { return x; };
        cassert((std::is_same_v<int&&, decltype(citrine::forward<int>(lexpr(value)))>));
        cassert((std::is_same_v<int&&, decltype(citrine::forward<int>(rexpr(value)))>));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
        cassert(citrine::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }))
        cassert(!citrine::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }))
    }
    {
        auto list = std::forward_list<int>{0, 1, 1, 3, 4, 5};
        cassert(citrine::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }));
        cassert(!citrine::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!citrine::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        cassert(!citrine::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }));
        cassert(!citrine::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }));
        cassert(!citrine::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
        cassert(citrine::all_of(list.begin(), list.end(), [](auto x){ return x < 6; }));
        cassert(!citrine::all_of(list.begin(), list.end(), [](auto x){ return x < 5; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        auto other = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        cassert(citrine::equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
        auto other = std::forward_list<int>{0, 1, 1, 3, 4, 5};
        cassert(!citrine::equal(list.begin(), list.end(), other.begin()));
    }
}
