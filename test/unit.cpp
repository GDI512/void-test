#include "common.hpp"

int main() {
    {
        test::unit("unit", [] { test::check(true); });
        test::unit("unit", [] { test::check_equal(0, 0); });
        cassert(test::aux::exit_value == test::aux::exit_code::success);
    }
    {
        test::unit("unit", [] { test::check(false); });
        test::unit("unit", [] { test::check_equal(0, 0); });
        cassert(test::aux::exit_value == test::aux::exit_code::failure);
    }
}
