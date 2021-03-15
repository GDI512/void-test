#include "common.hpp"

int main() {
    {
        test::unit("unit", [] { test::check(true); });
        test::unit("unit", [] { test::check_equal(0, 0); });
        cassert(test::on_exit() == test::exit_success);
    }
    {
        test::unit("unit", [] { test::check(false); });
        test::unit("unit", [] { test::check_equal(0, 0); });
        cassert(test::on_exit() == test::exit_failure);
    }
}
