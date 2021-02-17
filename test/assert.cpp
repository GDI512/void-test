#include "common.hpp"

using namespace test;

int main() {
    {
        cassert(check(true));
        cassert(!check(false));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(check(list.begin(), list.end(), [](auto x) { return x <= 7; }));
        cassert(!check(list.begin(), list.end(), [](auto x) { return x < 7; }));
    }
    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        cassert(check(array, [](auto x) { return x <= 7; }));
        cassert(!check(array, [](auto x) { return x < 7; }));
    }
    {
        cassert(check_equal(2, 2));
        cassert(!check_equal(2, 4));
    }
    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        int other[] = {0, 1, 2, 3, 4, 5, 6, 7};
        cassert(check_equal(array, other));
        cassert(check_equal(std::begin(array), std::end(array), std::begin(other)));
    }
    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        int other[] = {0, 1, 2, 4, 4, 5, 6, 7};
        cassert(!check_equal(array, other));
        cassert(!check_equal(std::begin(array), std::end(array), std::begin(other)));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(check_equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
        cassert(!check_equal(list.begin(), list.end(), other.begin()));
    }
    {
        cassert(check_not_equal(2, 4));
        cassert(!check_not_equal(2, 2));
    }
    {
        int array[] = {0, 1, 2, 4, 4, 5, 6, 7};
        int other[] = {0, 1, 2, 3, 4, 5, 6, 7};
        cassert(check_not_equal(array, other));
        cassert(check_not_equal(std::begin(array), std::end(array), std::begin(other)));
    }
    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        int other[] = {0, 1, 2, 3, 4, 5, 6, 7};
        cassert(!check_not_equal(array, other));
        cassert(!check_not_equal(std::begin(array), std::end(array), std::begin(other)));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
        cassert(check_not_equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(!check_not_equal(list.begin(), list.end(), other.begin()));
    }
    {
        cassert(check_less(2, 4));
        cassert(!check_less(2, 2));
        cassert(!check_less(2, 1));
    }
    {
        cassert(check_not_less(2, 2));
        cassert(check_not_less(4, 2));
        cassert(!check_not_less(1, 2));
    }
    {
        cassert(check_greater(4, 2));
        cassert(!check_greater(2, 2));
        cassert(!check_greater(1, 2));
    }
    {
        cassert(check_not_greater(2, 2));
        cassert(check_not_greater(2, 4));
        cassert(!check_not_greater(2, 1));
    }
    {
        cassert(check_throws([]() { throw 0; }));
        cassert(!check_throws([]() { return 0; }));
    }
    {
        cassert(check_nothrows([]() { return 0; }));
        cassert(!check_nothrows([]() { throw 0; }));
    }
    {
        int array[1] = {};
        cassert(check_sorted(array, [](auto x, auto y) { return x < y; }));
    }
    {
        int array[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        cassert(check_sorted(array, [](auto x, auto y) { return x < y; }));
    }
    {
        int array[8] = {0, 1, 1, 2, 2, 3, 3, 4};
        cassert(!check_sorted(array, [](auto x, auto y) { return x < y; }));
        cassert(check_sorted(array, [](auto x, auto y) { return x <= y; }));
    }
    {
        int array[8] = {7, 0, 1, 6, 5, 2, 3, 4};
        cassert(!check_sorted(array, [](auto x, auto y) { return x < y; }));
        cassert(!check_sorted(array, [](auto x, auto y) { return x <= y; }));
        cassert(!check_sorted(array, [](auto x, auto y) { return x > y; }));
        cassert(!check_sorted(array, [](auto x, auto y) { return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{};
        cassert(check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
    }
    {
        auto list = std::forward_list<int>{1};
        cassert(check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 1, 2, 2, 3, 3, 4};
        cassert(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        cassert(check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
    }
    {
        auto list = std::forward_list<int>{7, 0, 1, 6, 5, 2, 3, 4};
        cassert(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        cassert(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
        cassert(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }));
        cassert(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }));
    }
}
