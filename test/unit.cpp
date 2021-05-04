#include <assert.hpp>

template <auto N>
auto check() noexcept = delete;

template <>
auto check<0>() noexcept {
    test::unit("", [] { test::check(true); });
    test::unit("", [] { test::check_equal(0, 0); });
    if (test::exit_code != 0)
        return 1;
    return 0;
}

template <>
auto check<1>() noexcept {
    test::unit("", [] { test::check(false); });
    test::unit("", [] { test::check_equal(0, 0); });
    if (test::exit_code != 1)
        return 1;
    return 0;
}

int main() {
    auto exit_code = 0;
    exit_code += check<0>();
    exit_code += check<1>();
    return exit_code;
}
