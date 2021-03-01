#include "common.hpp"

#include <utility>
#include <new>

int main() {
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            instance.~object();
        }
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            new (&instance) test::object{};
        }
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            auto other = test::object{instance};
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            auto other = test::object{std::move(instance)};
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            instance.~object();
            auto other = test::object{instance};
        }
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            instance.~object();
            auto other = test::object{std::move(instance)};
        }
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance = other;
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance = std::move(other);
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance.~object();
            instance = other;
        }
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance.~object();
            instance = std::move(other);
        }
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            auto other = test::object{};
            other.~object();
            instance = other;
        }
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::object{};
            auto other = test::object{};
            other.~object();
            instance = std::move(other);
        }
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        auto instance = test::object{32};
        const auto other = test::object{16};
        cassert(instance == 32);
        cassert(other == 16);
    }
    {
        auto registry = test::core::registry{};
        auto instance = test::object{32};
        const auto other = test::object{16};
        instance = other;
        cassert(instance == 16);
        cassert(other == 16);
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::counter{};
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::counter{};
            auto other = test::counter{instance};
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::counter{};
            auto other = test::counter{std::move(instance)};
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::counter{};
            auto other = test::counter{};
            instance = other;
        }
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        {
            auto instance = test::counter{};
            auto other = test::counter{};
            instance = std::move(other);
        }
        cassert(registry.status());
    }
}
