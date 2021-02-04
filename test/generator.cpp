#include "common.hpp"

using namespace test;

int main() {
    {
        auto int_generator = test::generator<int>();
        auto float_generator = test::generator<float>();
        const auto x = int_generator();
        const auto y = float_generator();
        cassert(x >= 0 && x <= std::numeric_limits<int>::max());
        cassert(y >= 0.0 && y < 1.0f);
    }
    {
        auto array = test::array<int>();
        auto other = test::array<float>();
        cassert(array.size() == 0 && other.size() == 0);
        cassert(array.capacity() == 0 && other.capacity() == 0);
        cassert(array.data() == nullptr && other.data() == nullptr);
    }
    {
        auto array = test::array<int>(32);
        auto other = test::array<float>(32);
        cassert(array.size() == 32 && other.size() == 32);
        cassert(array.capacity() == 32 && other.capacity() == 32);
        cassert(array.data() != nullptr && other.data() != nullptr);
        for (auto x : array) {
            cassert(x == 0);
        }
        for (auto x : other) {
            cassert(x == 0.0f);
        }
    }
    {
        auto array = test::array<int>(32, 16);
        auto other = test::array<float>(32, 0.1f);
        cassert(array.size() == 32 && other.size() == 32);
        cassert(array.capacity() == 32 && other.capacity() == 32);
        cassert(array.data() != nullptr && other.data() != nullptr);
        for (auto x : array) {
            cassert(x == 16);
        }
        for (auto x : other) {
            cassert(x == 0.1f);
        }
    }
    {
        auto array = test::array<int>(32, 16);
        auto other = test::array<int>(array.begin(), array.end());
        cassert(other.size() == 32);
        cassert(other.capacity() == 32);
        cassert(other.data() != nullptr);
        for (auto x : other) {
            cassert(x == 16);
        }
    }
    {
        auto array = test::array<int>(32, 16);
        auto other = test::array<int>(array);
        cassert(other.size() == 32);
        cassert(other.capacity() == 32);
        cassert(other.data() != nullptr);
        for (auto x : other) {
            cassert(x == 16);
        }
    }
    {
        auto array = test::array<int>(32, 16);
        auto other = test::array<int>(std::move(array));
        cassert(other.size() == 32);
        cassert(other.capacity() == 32);
        cassert(other.data() != nullptr);
        for (auto x : other) {
            cassert(x == 16);
        }
    }
    {
        auto array = test::array<int>();
        auto other = test::array<int>(32, 16);
        array = other;
        cassert(array.size() == 32);
        cassert(array.capacity() == 32);
        cassert(array.data() != nullptr);
        for (auto x : array) {
            cassert(x == 16);
        }
    }
    {
        auto array = test::array<int>();
        auto other = test::array<int>(32, 16);
        array = std::move(other);
        cassert(array.size() == 32);
        cassert(array.capacity() == 32);
        cassert(array.data() != nullptr);
        for (auto x : array) {
            cassert(x == 16);
        }
    }
    {
        auto array = test::array<int>();
        auto other = test::array<int>(32, 16);
        array.swap(other);
        cassert(array.size() == 32 && other.size() == 0);
        cassert(array.capacity() == 32 && other.capacity() == 0);
        cassert(array.data() != nullptr && other.data() == nullptr);
        for (auto x : array) {
            cassert(x == 16);
        }
    }
    {
        auto array = test::array<int>(32);
        for (auto i = 0u; i < array.size(); i++) {
            array[i] = i;
        }
        for (auto i = 0u; i < array.size(); i++) {
            cassert(array[i] == i);
        }
    }
    {
        auto array = test::array<int>::random(8192, -16, 16);
        cassert(array.size() == 8192);
        cassert(array.capacity() == 8192);
        cassert(array.data() != nullptr);
        for (auto x : array) {
            cassert(x >= -16 && x <= 16);
        }
    }
    {
        auto array = test::array<float>::random(8192, -1.0f, 1.0f);
        cassert(array.size() == 8192);
        cassert(array.capacity() == 8192);
        cassert(array.data() != nullptr);
        for (auto x : array) {
            cassert(x >= -1.0f && x < 1.0f);
        }
    }
}
