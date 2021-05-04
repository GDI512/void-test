#include <assert.hpp>

#include <forward_list>

template <auto N>
auto check() noexcept = delete;

template <>
auto check<0>() noexcept {
    if (!test::check(true))
        return 1;
    if (test::check(false))
        return 1;
    return 0;
}

template <>
auto check<1>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    if (!test::check(list.begin(), list.end(), [](auto x) { return x <= 7; }))
        return 1;
    if (test::check(list.begin(), list.end(), [](auto x) { return x < 7; }))
        return 1;
    return 0;
}

template <>
auto check<2>() noexcept {
    if (!test::check_equal(2, 2))
        return 1;
    if (test::check_equal(2, 4))
        return 1;
    return 0;
}

template <>
auto check<3>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    if (!test::check_equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto check<4>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
    if (test::check_equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto check<5>() noexcept {
    if (!test::check_not_equal(2, 4))
        return 1;
    if (test::check_not_equal(2, 2))
        return 1;
    return 0;
}

template <>
auto check<6>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    auto other = std::forward_list<int>{0, 1, 2, 4, 4, 5, 6, 7};
    if (!test::check_not_equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto check<7>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    auto other = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    if (test::check_not_equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto check<8>() noexcept {
    if (!test::check_less(2, 4))
        return 1;
    if (test::check_less(2, 2))
        return 1;
    if (test::check_less(2, 1))
        return 1;
    return 0;
}

template <>
auto check<9>() noexcept {
    if (!test::check_not_less(2, 2))
        return 1;
    if (!test::check_not_less(4, 2))
        return 1;
    if (test::check_not_less(1, 2))
        return 1;
    return 0;
}

template <>
auto check<10>() noexcept {
    if (!test::check_greater(4, 2))
        return 1;
    if (test::check_greater(2, 2))
        return 1;
    if (test::check_greater(1, 2))
        return 1;
    return 0;
}

template <>
auto check<11>() noexcept {
    if (!test::check_not_greater(2, 2))
        return 1;
    if (!test::check_not_greater(2, 4))
        return 1;
    if (test::check_not_greater(2, 1))
        return 1;
    return 0;
}

template <>
auto check<12>() noexcept {
    if (!test::check_throws([]() { throw 0; }))
        return 1;
    if (test::check_throws([]() { return 0; }))
        return 1;
    return 0;
}

template <>
auto check<13>() noexcept {
    if (!test::check_nothrows([]() { return 0; }))
        return 1;
    if (test::check_nothrows([]() { throw 0; }))
        return 1;
    return 0;
}

template <>
auto check<14>() noexcept {
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
auto check<15>() noexcept {
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
auto check<16>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5, 6, 7};
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }))
        return 1;
    return 0;
}

template <>
auto check<17>() noexcept {
    auto list = std::forward_list<int>{0, 1, 1, 2, 2, 3, 3, 4};
    if (test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x < y; }))
        return 1;
    if (!test::check_sorted(list.begin(), list.end(), [](auto x, auto y) { return x <= y; }))
        return 1;
    return 0;
}

template <>
auto check<18>() noexcept {
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
auto check<19>() noexcept {
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
    exit_code += check<0>();
    exit_code += check<1>();
    exit_code += check<2>();
    exit_code += check<3>();
    exit_code += check<4>();
    exit_code += check<5>();
    exit_code += check<6>();
    exit_code += check<7>();
    exit_code += check<8>();
    exit_code += check<9>();
    exit_code += check<10>();
    exit_code += check<11>();
    exit_code += check<12>();
    exit_code += check<13>();
    exit_code += check<14>();
    exit_code += check<15>();
    exit_code += check<16>();
    exit_code += check<17>();
    exit_code += check<18>();
    exit_code += check<19>();
    return exit_code;
}
