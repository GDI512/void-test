#include "common.hpp"

int main() {
    {
        auto state = test::unit_state();
        state.on_error();
        cassert(!state.empty());
        cassert(!state.good());
    }
    {
        auto state = test::unit_state();
        state.on_success();
        cassert(!state.empty());
        cassert(state.good());
    }
    {
        auto state = test::unit_state();
        state.on_exception();
        cassert(!state.empty());
        cassert(!state.good());
    }
    {
        auto state = test::unit_state();
        state.on_destruction();
        cassert(!state.empty());
        cassert(!state.good());
    }
    {
        auto state = test::unit_state();
        state.on_construction();
        cassert(!state.empty());
        cassert(!state.good());
    }
    {
        auto state = test::unit_state();
        state.on_construction();
        state.on_destruction();
        cassert(!state.empty());
        cassert(state.good());
    }
    {
        auto state = test::unit_state();
        state.on_error();
        state.on_success();
        state.on_exception();
        state.on_destruction();
        state.on_construction();
        cassert(state.get().check_count == 2);
        cassert(state.get().error_count == 2);
        cassert(state.get().destroyed_count == 1);
        cassert(state.get().constructed_count == 1);
    }
}
