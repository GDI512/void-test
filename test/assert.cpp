#include "common.hpp"

#include <list>

using namespace test;

int main() {
    {
        cassert(check(true));
        cassert(!check(false));
    }
    {
        cassert(check([](auto x) { return x; }, true));
        cassert(!check([](auto x) { return x; }, false));
    }
    {
        cassert(check_equal(2, 2));
        cassert(!check_equal(2, 4));
    }
    {
        cassert(check_not_equal(2, 4));
        cassert(!check_not_equal(2, 2));
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
            auto list = std::list<int>{};
            cassert(check_sorted(list, [](auto x, auto y) { return x < y; }));
        }
        {
            auto list = std::list<int>{1};
            cassert(check_sorted(list, [](auto x, auto y) { return x < y; }));
        }
        {
            auto list = std::list<int>{0, 1, 2, 3, 4, 5, 6, 7};
            cassert(check_sorted(list, [](auto x, auto y) { return x < y; }));
        }
        {
            auto list = std::list<int>{0, 1, 1, 2, 2, 3, 3, 4};
            cassert(!check_sorted(list, [](auto x, auto y) { return x < y; }));
            cassert(check_sorted(list, [](auto x, auto y) { return x <= y; }));
        }
        {
            auto list = std::list<int>{7, 0, 1, 6, 5, 2, 3, 4};
            cassert(!check_sorted(list, [](auto x, auto y) { return x < y; }));
            cassert(!check_sorted(list, [](auto x, auto y) { return x <= y; }));
            cassert(!check_sorted(list, [](auto x, auto y) { return x > y; }));
            cassert(!check_sorted(list, [](auto x, auto y) { return x >= y; }));
        }
    }
}
