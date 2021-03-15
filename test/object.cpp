#include "common.hpp"

#include <utility>
#include <new>

int main() {
    {
        auto instance = test::object{4};
        auto other = test::object{2};
        cassert(instance == 4);
        cassert(other == 2);
        cassert(instance != other);
        cassert(!(instance == other));
    }
    {
        auto instance = test::object{4};
        auto other = test::object{2};
        instance = other;
        cassert(instance == 2);
        cassert(other == 2);
    }
    {
        auto instance = test::object{4};
        auto other = test::object{2};
        instance = std::move(other);
        cassert(instance == 2);
        cassert(other == 2);
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            instance.~object();
        }
        cassert(!context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            new (&instance) test::object{};
        }
        cassert(!context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{instance};
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{std::move(instance)};
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            instance.~object();
            auto other = test::object{instance};
        }
        cassert(!context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            instance.~object();
            auto other = test::object{std::move(instance)};
        }
        cassert(!context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance = other;
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance = std::move(other);
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance.~object();
            instance = other;
        }
        cassert(!context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance.~object();
            instance = std::move(other);
        }
        cassert(!context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            other.~object();
            instance = other;
        }
        cassert(!context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            other.~object();
            instance = std::move(other);
        }
        cassert(!context.good());
    }
    {
        auto context = test::registry("");
        auto instance = test::object{32};
        const auto other = test::object{16};
        cassert(instance == 32);
        cassert(other == 16);
    }
    {
        auto context = test::registry("");
        auto instance = test::object{32};
        const auto other = test::object{16};
        instance = other;
        cassert(instance == 16);
        cassert(other == 16);
    }
    {
        auto instance = test::counter{4};
        auto other = test::counter{2};
        cassert(instance == 4);
        cassert(other == 2);
        cassert(instance != other);
        cassert(!(instance == other));
    }
    {
        auto instance = test::counter{4};
        auto other = test::counter{2};
        instance = other;
        cassert(instance == 2);
        cassert(other == 2);
    }
    {
        auto instance = test::counter{4};
        auto other = test::counter{2};
        instance = std::move(other);
        cassert(instance == 2);
        cassert(other == 2);
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::counter{};
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::counter{};
            auto other = test::counter{instance};
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::counter{};
            auto other = test::counter{std::move(instance)};
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::counter{};
            auto other = test::counter{};
            instance = other;
        }
        cassert(context.good());
    }
    {
        auto context = test::registry("");
        {
            auto instance = test::counter{};
            auto other = test::counter{};
            instance = std::move(other);
        }
        cassert(context.good());
    }
}
