#include "common.hpp"

template <>
auto assert<0>() noexcept {
    if (!test::check(true))
        return 1;
    if (test::check(false))
        return 1;
    return 0;
}

template <>
auto assert<1>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    if (!test::check(list.begin(), list.end(), [](auto x) { return x <= 7; }))
        return 1;
    if (test::check(list.begin(), list.end(), [](auto x) { return x < 7; }))
        return 1;
    return 0;
}

template <>
auto assert<2>() noexcept {
    if (!test::check_equal(2, 2))
        return 1;
    if (test::check_equal(2, 4))
        return 1;
    return 0;
}

template <>
auto assert<3>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    if (!test::check_equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto assert<4>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
    if (test::check_equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto assert<5>() noexcept {
    if (!test::check_not_equal(2, 4))
        return 1;
    if (test::check_not_equal(2, 2))
        return 1;
    return 0;
}

template <>
auto assert<6>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
    if (!test::check_not_equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto assert<7>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    if (test::check_not_equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto assert<8>() noexcept {
    if (!test::check_less(2, 4))
        return 1;
    if (test::check_less(2, 2))
        return 1;
    if (test::check_less(2, 1))
        return 1;
    return 0;
}

template <>
auto assert<9>() noexcept {
    if (!test::check_not_less(2, 2))
        return 1;
    if (!test::check_not_less(4, 2))
        return 1;
    if (test::check_not_less(1, 2))
        return 1;
    return 0;
}

template <>
auto assert<10>() noexcept {
    if (!test::check_greater(4, 2))
        return 1;
    if (test::check_greater(2, 2))
        return 1;
    if (test::check_greater(1, 2))
        return 1;
    return 0;
}

template <>
auto assert<11>() noexcept {
    if (!test::check_not_greater(2, 2))
        return 1;
    if (!test::check_not_greater(2, 4))
        return 1;
    if (test::check_not_greater(2, 1))
        return 1;
    return 0;
}

template <>
auto assert<12>() noexcept {
    if (!test::check_throws([]() { throw 0; }))
        return 1;
    if (test::check_throws([]() { return 0; }))
        return 1;
    return 0;
}

template <>
auto assert<13>() noexcept {
    if (!test::check_nothrows([]() { return 0; }))
        return 1;
    if (test::check_nothrows([]() { throw 0; }))
        return 1;
    return 0;
}

template <>
auto assert<14>() noexcept {
    auto list = std::forward_list<int>{};
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }))
        return 1;
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }))
        return 1;
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }))
        return 1;
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }))
        return 1;
    return 0;
}

template <>
auto assert<15>() noexcept {
    auto list = std::forward_list<int>{1};
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }))
        return 1;
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }))
        return 1;
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }))
        return 1;
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }))
        return 1;
    return 0;
}

template <>
auto assert<16>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }))
        return 1;
    return 0;
}

template <>
auto assert<17>() noexcept {
    auto list = std::forward_list<int>{0, 1, 1, 2, 2, 3, 3, 4};
    if (test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }))
        return 1;
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }))
        return 1;
    return 0;
}

template <>
auto assert<18>() noexcept {
    auto list = std::forward_list<int>{7, 0, 1, 6, 5, 2, 3, 4};
    if (test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }))
        return 1;
    if (test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }))
        return 1;
    if (test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x > y; }))
        return 1;
    if (test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x >= y; }))
        return 1;
    return 0;
}

template <>
auto assert<19>() noexcept {
    auto list = std::forward_list<int>{7, 0, 1, 6, 5, 2, 3, 4};
    if (!test::check_contains(list.begin(), list.end(), 7))
        return 1;
    if (!test::check_contains(list.begin(), list.end(), 5))
        return 1;
    if (!test::check_contains(list.begin(), list.end(), 4))
        return 1;
    if (test::check_contains(list.begin(), list.end(), 8))
        return 1;
    return 0;
}

int main() {
    auto exit_code = 0;
    exit_code += assert<0>();
    exit_code += assert<1>();
    exit_code += assert<2>();
    exit_code += assert<3>();
    exit_code += assert<4>();
    exit_code += assert<5>();
    exit_code += assert<6>();
    exit_code += assert<7>();
    exit_code += assert<8>();
    exit_code += assert<9>();
    exit_code += assert<10>();
    exit_code += assert<11>();
    exit_code += assert<12>();
    exit_code += assert<13>();
    exit_code += assert<14>();
    exit_code += assert<15>();
    exit_code += assert<16>();
    exit_code += assert<17>();
    exit_code += assert<18>();
    exit_code += assert<19>();
    return exit_code;
}
