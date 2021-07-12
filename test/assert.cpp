#include "common.hpp"

#include <forward_list>

int main() {
    {
        auto state = test::unit_state();
        cassert(test::check(true));
        cassert(!test::check(false));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(test::check(list.begin(), list.end(), [](auto x) { return x <= 7; }));
        cassert(!test::check(list.begin(), list.end(), [](auto x) { return x < 7; }));
    }
    {
        auto state = test::unit_state();
        cassert(test::check_equal(2, 2));
        cassert(!test::check_equal(2, 4));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(test::check_equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
        cassert(!test::check_equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto state = test::unit_state();
        cassert(test::check_not_equal(2, 4));
        cassert(!test::check_not_equal(2, 2));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
        cassert(test::check_not_equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(!test::check_not_equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto state = test::unit_state();
        cassert(test::check_less(2, 4));
        cassert(!test::check_less(2, 2));
        cassert(!test::check_less(2, 1));
    }
    {
        auto state = test::unit_state();
        cassert(test::check_not_less(2, 2));
        cassert(test::check_not_less(4, 2));
        cassert(!test::check_not_less(1, 2));
    }
    {
        auto state = test::unit_state();
        cassert(test::check_greater(4, 2));
        cassert(!test::check_greater(2, 2));
        cassert(!test::check_greater(1, 2));
    }
    {
        auto state = test::unit_state();
        cassert(test::check_not_greater(2, 2));
        cassert(test::check_not_greater(2, 4));
        cassert(!test::check_not_greater(2, 1));
    }
    {
        auto state = test::unit_state();
        cassert(test::check_throws([]() { throw 0; }));
        cassert(!test::check_throws([]() { return 0; }));
    }
    {
        auto state = test::unit_state();
        cassert(test::check_nothrows([]() { return 0; }));
        cassert(!test::check_nothrows([]() { throw 0; }));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{};
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }));
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{1};
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }));
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{0, 1, 1, 2, 2, 3, 3, 4};
        cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{7, 0, 1, 6, 5, 2, 3, 4};
        cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
        cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }));
        cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }));
    }
    {
        auto state = test::unit_state();
        auto list = std::forward_list<int>{7, 0, 1, 6, 5, 2, 3, 4};
        cassert(test::check_contains(list.begin(), list.end(), 7));
        cassert(test::check_contains(list.begin(), list.end(), 5));
        cassert(test::check_contains(list.begin(), list.end(), 4));
        cassert(!test::check_contains(list.begin(), list.end(), 8));
    }
}
