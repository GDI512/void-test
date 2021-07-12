#include "common.hpp"

int main() {
    {
        test::unit("", [] { test::check(true); });
        test::unit("", [] { test::check_equal(0, 0); });
        cassert(test::exit_code == 0);
    }
    {
        test::unit("", [] { test::check(false); });
        test::unit("", [] { test::check_equal(0, 0); });
        cassert(test::exit_code == 1);
    }
}
