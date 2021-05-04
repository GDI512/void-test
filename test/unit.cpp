#include <assert.hpp>

template <auto N>
auto assert() noexcept = delete;

template <>
auto assert<0>() noexcept {
    test::unit("", [] { test::check(true); });
    test::unit("", [] { test::check_equal(0, 0); });
    if (test::exit_code != 0)
        return 1;
    return 0;
}

template <>
auto assert<1>() noexcept {
    test::unit("", [] { test::check(false); });
    test::unit("", [] { test::check_equal(0, 0); });
    if (test::exit_code != 1)
        return 1;
    return 0;
}

int main() {
    auto exit_code = 0;
    exit_code += assert<0>();
    exit_code += assert<1>();
    return exit_code;
}
