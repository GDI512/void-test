#include "common.hpp"

#include <utility>

int main() {
    {
        auto state = citrine::unit_state();
        const auto object = citrine::counter(4);
        const auto other = citrine::counter(2);
        cassert(object == 4);
        cassert(other == 2);
    }
    {
        auto state = citrine::unit_state();
        auto object = citrine::counter(4);
        const auto other = citrine::counter(2);
        object = other;
        cassert(object == 2);
        cassert(other == 2);
    }
    {
        auto state = citrine::unit_state();
        auto object = citrine::counter(4);
        auto other = citrine::counter(2);
        object = std::move(other);
        cassert(object == 2);
        cassert(other == 2);
    }
    {
        auto state = citrine::unit_state();
        {
            auto object = citrine::counter();
        }
        cassert(state.get().destroyed_count == 1);
        cassert(state.get().constructed_count == 1);
    }
    {
        auto state = citrine::unit_state();
        {
            auto object = citrine::counter();
            auto other = citrine::counter(object);
        }
        cassert(state.get().destroyed_count == 2);
        cassert(state.get().constructed_count == 2);
    }
    {
        auto state = citrine::unit_state();
        {
            auto object = citrine::counter();
            auto other = citrine::counter(std::move(object));
        }
        cassert(state.get().destroyed_count == 2);
        cassert(state.get().constructed_count == 2);
    }
    {
        auto state = citrine::unit_state();
        {
            auto object = citrine::counter();
            auto other = citrine::counter();
            object = other;
        }
        cassert(state.get().destroyed_count == 2);
        cassert(state.get().constructed_count == 2);
    }
    {
        auto state = citrine::unit_state();
        {
            auto object = citrine::counter();
            auto other = citrine::counter();
            object = std::move(other);
        }
        cassert(state.get().destroyed_count == 2);
        cassert(state.get().constructed_count == 2);
    }
}
