#include <state.hpp>

template <auto N>
auto assert() noexcept = delete;

template <>
auto assert<0>() noexcept {
    test::current = {};
    test::report<test::message::error>();
    if (test::current.total_count != 1)
        return 1;
    if (test::current.error_count != 1)
        return 1;
    return 0;
}

template <>
auto assert<1>() noexcept {
    test::current = {};
    test::report<test::message::success>();
    if (test::current.total_count != 1)
        return 1;
    if (test::current.error_count != 0)
        return 1;
    return 0;
}

template <>
auto assert<2>() noexcept {
    test::current = {};
    test::report<test::message::exception>();
    if (test::current.total_count != 0)
        return 1;
    if (test::current.error_count != 1)
        return 1;
    return 0;
}

template <>
auto assert<3>() noexcept {
    test::current = {};
    test::report<test::message::destructor>();
    if (test::current.destroyed_count != 1)
        return 1;
    if (test::current.constructed_count != 0)
        return 1;
    return 0;
}

template <>
auto assert<4>() noexcept {
    test::current = {};
    test::report<test::message::constructor>();
    if (test::current.destroyed_count != 0)
        return 1;
    if (test::current.constructed_count != 1)
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
    return exit_code;
}
