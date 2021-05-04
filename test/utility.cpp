#include <utility.hpp>

#include <forward_list>
#include <type_traits>
#include <utility>

template <auto N>
auto assert() noexcept = delete;

template <>
auto assert<0>() noexcept {
    if (!std::is_same_v<int, typename test::remove_reference<int>::type>)
        return 1;
    if (!std::is_same_v<int, typename test::remove_reference<int&>::type>)
        return 1;
    if (!std::is_same_v<int, typename test::remove_reference<int&&>::type>)
        return 1;
    return 0;
}

template <>
auto assert<1>() noexcept {
    if (!test::is_lvalue_reference<int&>::value)
        return 1;
    if (test::is_lvalue_reference<int>::value)
        return 1;
    if (test::is_lvalue_reference<int&&>::value)
        return 1;
    return 0;
}

template <>
auto assert<2>() noexcept {
    auto value = 4;
    auto rvalue = [](int x) -> int { return x; };
    auto lvalue = [](int& x) -> int& { return x; };
    if (!std::is_same_v<int&&, decltype(test::forward<int>(lvalue(value)))>)
        return 1;
    if (!std::is_same_v<int&&, decltype(test::forward<int>(rvalue(value)))>)
        return 1;
    return 0;
}

template <>
auto assert<3>() noexcept {
auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
    if (!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }))
        return 1;
    if (test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }))
        return 1;
    return 0;
}

template <>
auto assert<4>() noexcept {
    auto list = std::forward_list<int>{0, 1, 1, 3, 4, 5};
    if (!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }))
        return 1;
    if (test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }))
        return 1;
    if (test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }))
        return 1;
    return 0;
}

template <>
auto assert<5>() noexcept {
    auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
    if (test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }))
        return 1;
    if (test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x <= y; }))
        return 1;
    if (test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }))
        return 1;
    return 0;
}

template <>
auto assert<6>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
    if (!test::all_of(list.begin(), list.end(), [](auto x){ return x < 6; }))
        return 1;
    if (test::all_of(list.begin(), list.end(), [](auto x){ return x < 5; }))
        return 1;
    return 0;
}

template <>
auto assert<7>() noexcept {
    auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
    auto other = std::forward_list<int>{0, 1, 0, 3, 4, 5};
    if (!test::equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto assert<8>() noexcept {
    auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
    auto other = std::forward_list<int>{0, 1, 1, 3, 4, 5};
    if (test::equal(list.begin(), list.end(), other.begin()))
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
    return exit_code;
}
