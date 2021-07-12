#include "common.hpp"

int main() {
    {
        citrine::unit("", [] { citrine::check(true); });
        citrine::unit("", [] { citrine::check_equal(0, 0); });
        cassert(citrine::exit_code == 0);
    }
    {
        citrine::unit("", [] { citrine::check(false); });
        citrine::unit("", [] { citrine::check_equal(0, 0); });
        cassert(citrine::exit_code == 1);
    }
}
