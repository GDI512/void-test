#include "common.hpp"

#include <forward_list>

using namespace test;

int main() {
    {
        CASSERT(check(true));
        CASSERT(!check(false));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(check(list.begin(), list.end(), [](auto x) { return x <= 7; }));
        CASSERT(!check(list.begin(), list.end(), [](auto x) { return x < 7; }));
    }
    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(check(array, [](auto x) { return x <= 7; }));
        CASSERT(!check(array, [](auto x) { return x < 7; }));
    }
    {
        CASSERT(check_equal(2, 2));
        CASSERT(!check_equal(2, 4));
    }
    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        int other[] = {0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(check_equal(array, other));
        CASSERT(check_equal(std::begin(array), std::end(array), std::begin(other)));
    }
    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        int other[] = {0, 1, 2, 4, 4, 5, 6, 7};
        CASSERT(!check_equal(array, other));
        CASSERT(!check_equal(std::begin(array), std::end(array), std::begin(other)));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(check_equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
        CASSERT(!check_equal(list.begin(), list.end(), other.begin()));
    }
    {
        CASSERT(check_not_equal(2, 4));
        CASSERT(!check_not_equal(2, 2));
    }
    {
        int array[] = {0, 1, 2, 4, 4, 5, 6, 7};
        int other[] = {0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(check_not_equal(array, other));
        CASSERT(check_not_equal(std::begin(array), std::end(array), std::begin(other)));
    }
    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
        int other[] = {0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(!check_not_equal(array, other));
        CASSERT(!check_not_equal(std::begin(array), std::end(array), std::begin(other)));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
        CASSERT(check_not_equal(list.begin(), list.end(), other.begin()));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(!check_not_equal(list.begin(), list.end(), other.begin()));
    }
    {
        CASSERT(check_less(2, 4));
        CASSERT(!check_less(2, 2));
        CASSERT(!check_less(2, 1));
    }
    {
        CASSERT(check_not_less(2, 2));
        CASSERT(check_not_less(4, 2));
        CASSERT(!check_not_less(1, 2));
    }
    {
        CASSERT(check_greater(4, 2));
        CASSERT(!check_greater(2, 2));
        CASSERT(!check_greater(1, 2));
    }
    {
        CASSERT(check_not_greater(2, 2));
        CASSERT(check_not_greater(2, 4));
        CASSERT(!check_not_greater(2, 1));
    }
    {
        CASSERT(check_throws([]() { throw 0; }));
        CASSERT(!check_throws([]() { return 0; }));
    }
    {
        CASSERT(check_nothrows([]() { return 0; }));
        CASSERT(!check_nothrows([]() { throw 0; }));
    }
    {
        int array[1] = {};
        CASSERT(check_sorted(array, [](auto x, auto y) { return x < y; }));
    }
    {
        int array[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(check_sorted(array, [](auto x, auto y) { return x < y; }));
    }
    {
        int array[8] = {0, 1, 1, 2, 2, 3, 3, 4};
        CASSERT(!check_sorted(array, [](auto x, auto y) { return x < y; }));
        CASSERT(check_sorted(array, [](auto x, auto y) { return x <= y; }));
    }
    {
        int array[8] = {7, 0, 1, 6, 5, 2, 3, 4};
        CASSERT(!check_sorted(array, [](auto x, auto y) { return x < y; }));
        CASSERT(!check_sorted(array, [](auto x, auto y) { return x <= y; }));
        CASSERT(!check_sorted(array, [](auto x, auto y) { return x > y; }));
        CASSERT(!check_sorted(array, [](auto x, auto y) { return x >= y; }));
    }
    {
        auto list = std::forward_list<int>{};
        CASSERT(check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
    }
    {
        auto list = std::forward_list<int>{1};
        CASSERT(check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        CASSERT(check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
    }
    {
        auto list = std::forward_list<int>{0, 1, 1, 2, 2, 3, 3, 4};
        CASSERT(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        CASSERT(check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
    }
    {
        auto list = std::forward_list<int>{7, 0, 1, 6, 5, 2, 3, 4};
        CASSERT(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        CASSERT(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
        CASSERT(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }));
        CASSERT(!check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }));
    }
}
