#include <utility.hpp>

#include <forward_list>
#include <type_traits>
#include <utility>

template <auto N>
auto check() noexcept = delete;

template <>
auto check<0>() noexcept {
    if (!std::is_same_v<int, typename test::remove_reference<int>::type>)
        return 1;
    if (!std::is_same_v<int, typename test::remove_reference<int&>::type>)
        return 1;
    if (!std::is_same_v<int, typename test::remove_reference<int&&>::type>)
        return 1;
    return 0;
}

template <>
auto check<1>() noexcept {
    if (!test::is_lvalue_reference<int&>::value)
        return 1;
    if (test::is_lvalue_reference<int>::value)
        return 1;
    if (test::is_lvalue_reference<int&&>::value)
        return 1;
    return 0;
}

template <>
auto check<2>() noexcept {
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
auto check<3>() noexcept {
auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
    if (!test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x < y; }))
        return 1;
    if (test::is_sorted(list.begin(), list.end(), [](auto x, auto y){ return x >= y; }))
        return 1;
    return 0;
}

template <>
auto check<4>() noexcept {
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
auto check<5>() noexcept {
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
auto check<6>() noexcept {
    auto list = std::forward_list<int>{0, 1, 2, 3, 4, 5};
    if (!test::all_of(list.begin(), list.end(), [](auto x){ return x < 6; }))
        return 1;
    if (test::all_of(list.begin(), list.end(), [](auto x){ return x < 5; }))
        return 1;
    return 0;
}

template <>
auto check<7>() noexcept {
    auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
    auto other = std::forward_list<int>{0, 1, 0, 3, 4, 5};
    if (!test::equal(list.begin(), list.end(), other.begin()))
        return 1;
    return 0;
}

template <>
auto check<8>() noexcept {
    auto list = std::forward_list<int>{0, 1, 0, 3, 4, 5};
    auto other = std::forward_list<int>{0, 1, 1, 3, 4, 5};
    if (test::equal(list.begin(), list.end(), other.begin()))
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
    return exit_code;
}
