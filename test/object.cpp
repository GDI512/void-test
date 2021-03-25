#include "common.hpp"

#include <utility>
#include <new>

int main() {
    { // 1.
        auto instance = test::object{4};
        auto other = test::object{2};
        cassert(instance == 4);
        cassert(other == 2);
        cassert(instance != other);
        cassert(!(instance == other));
    }
    { // 2.
        auto instance = test::object{4};
        auto other = test::object{2};
        instance = other;
        cassert(instance == 2);
        cassert(other == 2);
    }
    { // 3.
        auto instance = test::object{4};
        auto other = test::object{2};
        instance = std::move(other);
        cassert(instance == 2);
        cassert(other == 2);
    }
    { // 4.
        auto context = test::registry("");
        {
            auto instance = test::object{};
        }
        cassert(context.ok());
    }
    { // 5.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            instance.~object();
        }
        cassert(!context.ok());
    }
    { // 6.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            new (&instance) test::object{};
        }
        cassert(!context.ok());
    }
    { // 7.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{instance};
        }
        cassert(context.ok());
    }
    { // 8.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{std::move(instance)};
        }
        cassert(context.ok());
    }
    { // 9.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            instance.~object();
            auto other = test::object{instance};
        }
        cassert(!context.ok());
    }
    { // 10.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            instance.~object();
            auto other = test::object{std::move(instance)};
        }
        cassert(!context.ok());
    }
    { // 11.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance = other;
        }
        cassert(context.ok());
    }
    { // 12.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance = std::move(other);
        }
        cassert(context.ok());
    }
    { // 13.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance.~object();
            instance = other;
        }
        cassert(!context.ok());
    }
    { // 14.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            instance.~object();
            instance = std::move(other);
        }
        cassert(!context.ok());
    }
    { // 15.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            other.~object();
            instance = other;
        }
        cassert(!context.ok());
    }
    { // 16.
        auto context = test::registry("");
        {
            auto instance = test::object{};
            auto other = test::object{};
            other.~object();
            instance = std::move(other);
        }
        cassert(!context.ok());
    }
    { // 17.
        auto context = test::registry("");
        auto instance = test::object{32};
        const auto other = test::object{16};
        cassert(instance == 32);
        cassert(other == 16);
    }
    { // 18.
        auto context = test::registry("");
        auto instance = test::object{32};
        const auto other = test::object{16};
        instance = other;
        cassert(instance == 16);
        cassert(other == 16);
    }
    { // 19.
        auto instance = test::counter{4};
        auto other = test::counter{2};
        cassert(instance == 4);
        cassert(other == 2);
        cassert(instance != other);
        cassert(!(instance == other));
    }
    { // 20.
        auto instance = test::counter{4};
        auto other = test::counter{2};
        instance = other;
        cassert(instance == 2);
        cassert(other == 2);
    }
    { // 21.
        auto instance = test::counter{4};
        auto other = test::counter{2};
        instance = std::move(other);
        cassert(instance == 2);
        cassert(other == 2);
    }
    { // 22.
        auto context = test::registry("");
        {
            auto instance = test::counter{};
        }
        cassert(context.ok());
    }
    { // 23.
        auto context = test::registry("");
        {
            auto instance = test::counter{};
            auto other = test::counter{instance};
        }
        cassert(context.ok());
    }
    { // 24.
        auto context = test::registry("");
        {
            auto instance = test::counter{};
            auto other = test::counter{std::move(instance)};
        }
        cassert(context.ok());
    }
    { // 25.
        auto context = test::registry("");
        {
            auto instance = test::counter{};
            auto other = test::counter{};
            instance = other;
        }
        cassert(context.ok());
    }
    { // 26.
        auto context = test::registry("");
        {
            auto instance = test::counter{};
            auto other = test::counter{};
            instance = std::move(other);
        }
        cassert(context.ok());
    }
}
