// ================================================================
//  Description:
//      Source file containing tests related to assertions exposed
//      in the API. All assertions return true on success and
//      false on failure.
//
//  Content:
//        1. Simple bool assertion
//        2. Generic range-based assertion using forward iterators
//        3. Equality assertion
//        4. Range-based equality assertion using forward
//           iterators
//        6. Inequality assertion
//        7. Range-based inequality assertion using forward
//           iterators
//        9. Less-than assertion
//       10. Not-less-than assertion
//       11. Greater-than assertion
//       12. Not-greater-than assertion
//       13. Assertion that ensures the function argument throws
//       14. Assertion that ensures the function argument does not
//           throw
//       15. Assertion that checks if the given range (delimited
//           by forward iterators) is sorted
//       16. Assertion that checks if the given range (delimited
//           by forward iterators) contains the specified element
// ================================================================

#include "common.hpp"

#include <forward_list>
#include <utility>

int main() {
    { // 1.
        cassert(test::check(true));
        cassert(!test::check(false));
    }
    { // 2.
        auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
        cassert(test::check(list.begin(), list.end(), [](auto x) { return x <= 7; }));
        cassert(!test::check(list.begin(), list.end(), [](auto x) { return x < 7; }));
    }
    { // 3.
        cassert(test::check_equal(2, 2));
        cassert(!test::check_equal(2, 4));
    }
    { // 4.
        {
            auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
            auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
            cassert(test::check_equal(list.begin(), list.end(), other.begin()));
        }
        {
            auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
            auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
            cassert(!test::check_equal(list.begin(), list.end(), other.begin()));
        }
    }
    { // 6.
        cassert(test::check_not_equal(2, 4));
        cassert(!test::check_not_equal(2, 2));
    }
    { // 7.
        {
            auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
            auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
            cassert(test::check_not_equal(list.begin(), list.end(), other.begin()));
        }
        {
            auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
            auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
            cassert(!test::check_not_equal(list.begin(), list.end(), other.begin()));
        }
    }
    { // 9.
        cassert(test::check_less(2, 4));
        cassert(!test::check_less(2, 2));
        cassert(!test::check_less(2, 1));
    }
    { // 10.
        cassert(test::check_not_less(2, 2));
        cassert(test::check_not_less(4, 2));
        cassert(!test::check_not_less(1, 2));
    }
    { // 11.
        cassert(test::check_greater(4, 2));
        cassert(!test::check_greater(2, 2));
        cassert(!test::check_greater(1, 2));
    }
    { // 12.
        cassert(test::check_not_greater(2, 2));
        cassert(test::check_not_greater(2, 4));
        cassert(!test::check_not_greater(2, 1));
    }
    { // 13.
        cassert(test::check_throws([]() { throw 0; }));
        cassert(!test::check_throws([]() { return 0; }));
    }
    { // 14.
        cassert(test::check_nothrows([]() { return 0; }));
        cassert(!test::check_nothrows([]() { throw 0; }));
    }
    { // 15.
        {
            auto list = std::forward_list<int>{};
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }));
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }));
        }
        {
            auto list = std::forward_list<int>{1};
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }));
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }));
        }
        {
            auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
        }
        {
            auto list = std::forward_list<int>{0, 1, 1, 2, 2, 3, 3, 4};
            cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
            cassert(test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
        }
        {
            auto list = std::forward_list<int>{7, 0, 1, 6, 5, 2, 3, 4};
            cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }));
            cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }));
            cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }));
            cassert(!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }));
        }
    }
    { // 16.
        auto list = std::forward_list<int>{7, 0, 1, 6, 5, 2, 3, 4};
        cassert(test::check_contains(list.begin(), list.end(), 7));
        cassert(test::check_contains(list.begin(), list.end(), 5));
        cassert(test::check_contains(list.begin(), list.end(), 4));
        cassert(!test::check_contains(list.begin(), list.end(), 8));
    }
}
