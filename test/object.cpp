#include "common.hpp"

template <>
auto assert<0>() noexcept {
    const auto instance = test::counter(4);
    const auto other = test::counter(2);
    if (instance != 4)
        return 1;
    if (other != 2)
        return 1;
    if (instance == other)
        return 1;
    return 0;
}

template <>
auto assert<1>() noexcept {
    auto instance = test::counter(4);
    const auto other = test::counter(2);
    instance = other;
    if (instance != 2)
        return 1;
    if (other != 2)
        return 1;
    return 0;
}

template <>
auto assert<2>() noexcept {
    auto instance = test::counter(4);
    auto other = test::counter(2);
    instance = std::move(other);
    if (instance != 2)
        return 1;
    if (other != 2)
        return 1;
    return 0;
}

template <>
auto assert<3>() noexcept {
    { test::current = {};
      auto instance = test::counter(); };
    if (test::current.destroyed_count != 1)
        return 1;
    if (test::current.constructed_count != 1)
        return 1;
    return 0;
}

template <>
auto assert<4>() noexcept {
    { test::current = {};
      auto instance = test::counter();
      auto other = test::counter(instance); };
    if (test::current.destroyed_count != 2)
        return 1;
    if (test::current.constructed_count != 2)
        return 1;
    return 0;
}

template <>
auto assert<5>() noexcept {
    { test::current = {};
      auto instance = test::counter();
      auto other = test::counter(std::move(instance)); }
    if (test::current.destroyed_count != 2)
        return 1;
    if (test::current.constructed_count != 2)
        return 1;
    return 0;
}

template <>
auto assert<6>() noexcept {
    { test::current = {};
      auto instance = test::counter();
      auto other = test::counter();
      instance = other; }
    if (test::current.destroyed_count != 2)
        return 1;
    if (test::current.constructed_count != 2)
        return 1;
    return 0;
}

template <>
auto assert<7>() noexcept {
    { test::current = {};
      auto instance = test::counter();
      auto other = test::counter();
      instance = std::move(other); }
    if (test::current.destroyed_count != 2)
        return 1;
    if (test::current.constructed_count != 2)
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
    return exit_code;
}
