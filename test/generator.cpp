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
        auto random_int = test::generator<int>::get();
        auto random_float = test::generator<float>::get();
        cassert(random_int >= 0 && random_int <= std::numeric_limits<int>::max());
        cassert(random_float >= 0.0 && random_float < 1.0f);
    }
    {
        auto range = test::range<int>();
        auto other = test::range<float>();
        cassert(range.size() == 0 && other.size() == 0);
        cassert(range.capacity() == 0 && other.capacity() == 0);
        cassert(range.data() == nullptr && other.data() == nullptr);
    }
    {
        auto range = test::range<int>(32);
        auto other = test::range<float>(32);
        cassert(range.size() == 32 && other.size() == 32);
        cassert(range.capacity() == 32 && other.capacity() == 32);
        cassert(range.data() != nullptr && other.data() != nullptr);
        for (auto x : range) {
            cassert(x == 0);
        }
        for (auto x : other) {
            cassert(x == 0.0f);
        }
    }
    {
        auto range = test::range<int>(32, 16);
        auto other = test::range<float>(32, 0.1f);
        cassert(range.size() == 32 && other.size() == 32);
        cassert(range.capacity() == 32 && other.capacity() == 32);
        cassert(range.data() != nullptr && other.data() != nullptr);
        for (auto x : range) {
            cassert(x == 16);
        }
        for (auto x : other) {
            cassert(x == 0.1f);
        }
    }
    {
        auto range = test::range<int>(32, 16);
        auto other = test::range<int>(range.begin(), range.end());
        cassert(other.size() == 32);
        cassert(other.capacity() == 32);
        cassert(other.data() != nullptr);
        for (auto x : other) {
            cassert(x == 16);
        }
    }
    {
        auto range = test::range<int>(32, 16);
        auto other = test::range<int>(range);
        cassert(other.size() == 32);
        cassert(other.capacity() == 32);
        cassert(other.data() != nullptr);
        for (auto x : other) {
            cassert(x == 16);
        }
    }
    {
        auto range = test::range<int>(32, 16);
        auto other = test::range<int>(std::move(range));
        cassert(other.size() == 32);
        cassert(other.capacity() == 32);
        cassert(other.data() != nullptr);
        for (auto x : other) {
            cassert(x == 16);
        }
    }
    {
        auto range = test::range<int>();
        auto other = test::range<int>(32, 16);
        range = other;
        cassert(range.size() == 32);
        cassert(range.capacity() == 32);
        cassert(range.data() != nullptr);
        for (auto x : range) {
            cassert(x == 16);
        }
    }
    {
        auto range = test::range<int>();
        auto other = test::range<int>(32, 16);
        range = std::move(other);
        cassert(range.size() == 32);
        cassert(range.capacity() == 32);
        cassert(range.data() != nullptr);
        for (auto x : range) {
            cassert(x == 16);
        }
    }
    {
        auto range = test::range<int>();
        auto other = test::range<int>(32, 16);
        range.swap(other);
        cassert(range.size() == 32 && other.size() == 0);
        cassert(range.capacity() == 32 && other.capacity() == 0);
        cassert(range.data() != nullptr && other.data() == nullptr);
        for (auto x : range) {
            cassert(x == 16);
        }
    }
    {
        auto range = test::range<int>(32);
        for (auto i = 0u; i < range.size(); i++) {
            range[i] = i;
        }
        for (auto i = 0u; i < range.size(); i++) {
            cassert(range[i] == i);
        }
    }
    {
        auto range = test::range<int>::random(8192, -16, 16);
        cassert(range.size() == 8192);
        cassert(range.capacity() == 8192);
        cassert(range.data() != nullptr);
        for (auto x : range) {
            cassert(x >= -16 && x <= 16);
        }
    }
    {
        auto range = test::range<float>::random(8192, -1.0f, 1.0f);
        cassert(range.size() == 8192);
        cassert(range.capacity() == 8192);
        cassert(range.data() != nullptr);
        for (auto x : range) {
            cassert(x >= -1.0f && x < 1.0f);
        }
    }
    {
        auto range = test::range<int>::sequence(8192, 1, 1);
        cassert(range.size() == 8192);
        cassert(range.capacity() == 8192);
        cassert(range.data() != nullptr);
        cassert(range.front() == 1);
        cassert(range.back() == 8192);
        for (auto i = 0u; i < range.size(); i++) {
            cassert(range[i] == i * 1 + 1);
        }
    }
    {
        auto range = test::range<float>::sequence(16, 0.0f, 1.0f);
        cassert(range.size() == 16);
        cassert(range.capacity() == 16);
        cassert(range.data() != nullptr);
        cassert(range.front() == 0.0f);
        cassert(range.back() == 15.0f);
        for (auto i = 0u; i < range.size(); i++) {
            cassert(range[i] == i * 1.0f + 0.0f);
        }
    }
}
