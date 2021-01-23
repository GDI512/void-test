#include "common.hpp"

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
}
