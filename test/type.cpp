#include "common.hpp"

#include <utility>

int main() {
    {
        auto state = test::unit_state();
        const auto object = test::counter(4);
        const auto other = test::counter(2);
        cassert(object == 4);
        cassert(other == 2);
    }
    {
        auto state = test::unit_state();
        auto object = test::counter(4);
        const auto other = test::counter(2);
        object = other;
        cassert(object == 2);
        cassert(other == 2);
    }
    {
        auto state = test::unit_state();
        auto object = test::counter(4);
        auto other = test::counter(2);
        object = std::move(other);
        cassert(object == 2);
        cassert(other == 2);
    }
    {
        auto state = test::unit_state();
        {
            auto object = test::counter();
        }
        cassert(state.get().destroyed_count == 1);
        cassert(state.get().constructed_count == 1);
    }
    {
        auto state = test::unit_state();
        {
            auto object = test::counter();
            auto other = test::counter(object);
        }
        cassert(state.get().destroyed_count == 2);
        cassert(state.get().constructed_count == 2);
    }
    {
        auto state = test::unit_state();
        {
            auto object = test::counter();
            auto other = test::counter(std::move(object));
        }
        cassert(state.get().destroyed_count == 2);
        cassert(state.get().constructed_count == 2);
    }
    {
        auto state = test::unit_state();
        {
            auto object = test::counter();
            auto other = test::counter();
            object = other;
        }
        cassert(state.get().destroyed_count == 2);
        cassert(state.get().constructed_count == 2);
    }
    {
        auto state = test::unit_state();
        {
            auto object = test::counter();
            auto other = test::counter();
            object = std::move(other);
        }
        cassert(state.get().destroyed_count == 2);
        cassert(state.get().constructed_count == 2);
    }
}
