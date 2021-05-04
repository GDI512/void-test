#include <state.hpp>
#include <type.hpp>

#include <utility>

template <auto N>
auto check() noexcept = delete;

template <>
auto check<0>() noexcept {
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
auto check<1>() noexcept {
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
auto check<2>() noexcept {
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
auto check<3>() noexcept {
    { test::current = {};
      auto instance = test::counter(); };
    if (test::current.destroyed_count != 1)
        return 1;
    if (test::current.constructed_count != 1)
        return 1;
    return 0;
}

template <>
auto check<4>() noexcept {
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
auto check<5>() noexcept {
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
auto check<6>() noexcept {
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
auto check<7>() noexcept {
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
    exit_code += check<0>();
    exit_code += check<1>();
    exit_code += check<2>();
    exit_code += check<3>();
    exit_code += check<4>();
    exit_code += check<5>();
    exit_code += check<6>();
    exit_code += check<7>();
    return exit_code;
}
