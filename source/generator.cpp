#include <generator.hpp>
#include <random>

namespace test {

    template <typename T>
    range<T>::~range() noexcept {
        delete[] buffer;
    }

    template <typename T>
    range<T>::range() noexcept : buffer(), buffer_size() {}

    template <typename T>
    range<T>::range(size_type size, value_type value) {
        auto memory = new value_type[size];
        for (auto i = 0u; i < size; i++) {
            memory[i] = value;
        }
        buffer = memory;
        buffer_size = size;
    }

    template <typename T>
    range<T>::range(const_iterator first, const_iterator last) {
        auto size = last - first;
        auto memory = new value_type[size];
        for (auto i = 0; i < size; i++) {
            memory[i] = first[i];
        }
        buffer = memory;
        buffer_size = size;
    }

    template <typename T>
    range<T>::range(range&& other) noexcept {
        buffer = core::exchange(other.buffer, nullptr);
        buffer_size = core::exchange(other.buffer_size, 0u);
    }

    template <typename T>
    range<T>::range(const range& other) {
        auto memory = new value_type[other.size()];
        for (auto i = 0u; i < other.size(); i++) {
            memory[i] = other[i];
        }
        buffer = memory;
        buffer_size = other.size();
    }

    template <typename T>
    auto range<T>::operator=(range&& other) noexcept -> range& {
        range(core::move(other)).swap(*this);
        return *this;
    }

    template <typename T>
    auto range<T>::operator=(const range& other) -> range& {
        range(other).swap(*this);
        return *this;
    }

    template <typename T>
    auto range<T>::operator[](size_type index) noexcept -> reference {
        return buffer[index];
    }

    template <typename T>
    auto range<T>::operator[](size_type index) const noexcept -> const_reference {
        return buffer[index];
    }

    template <typename T>
    auto range<T>::swap(range& other) noexcept -> void {
        using test::swap;
        swap(*this, other);
    }

    template <typename T>
    auto range<T>::data() noexcept -> pointer {
        return buffer;
    }

    template <typename T>
    auto range<T>::data() const noexcept -> pointer {
        return buffer;
    }

    template <typename T>
    auto range<T>::front() noexcept -> reference {
        return *buffer;
    }

    template <typename T>
    auto range<T>::front() const noexcept -> const_reference {
        return *buffer;
    }

    template <typename T>
    auto range<T>::back() noexcept -> reference {
        return *(buffer + buffer_size - 1);
    }

    template <typename T>
    auto range<T>::back() const noexcept -> const_reference {
        return *(buffer + buffer_size - 1);
    }

    template <typename T>
    auto range<T>::begin() noexcept -> iterator {
        return buffer;
    }

    template <typename T>
    auto range<T>::begin() const noexcept -> const_iterator {
        return buffer;
    }

    template <typename T>
    auto range<T>::end() noexcept -> iterator {
        return buffer + buffer_size;
    }

    template <typename T>
    auto range<T>::end() const noexcept -> const_iterator {
        return buffer + buffer_size;
    }

    template <typename T>
    auto range<T>::empty() const noexcept -> bool {
        return buffer_size == 0;
    }

    template <typename T>
    auto range<T>::size() const noexcept -> size_type {
        return buffer_size;
    }

    template <typename T>
    auto range<T>::capacity() const noexcept -> size_type {
        return buffer_size;
    }

    template <typename T>
    auto range<T>::random(size_type size, value_type min, value_type max) -> range {
        if constexpr (core::is_same_v<value_type, int>) {
            auto source = generator<int>();
            auto array = range(size);
            for (auto& item : array) {
                item = source() % (max - min + 1) + min;
            }
            return array;
        } else if (core::is_same_v<value_type, float>) {
            auto source = generator<float>();
            auto array = range(size);
            for (auto& item : array) {
                item = source() * (max - min) + min;
            }
            return array;
        }
    }

    template <typename T>
    auto range<T>::sequence(size_type size, value_type start, value_type step) -> range {
        auto array = range(size);
        for (auto i = 0u; i < array.size(); i++) {
            array[i] = i * step + start;
        }
        return array;
    }

    template <>
    struct generator<int>::impl {
        std::random_device source;
        std::uniform_int_distribution<int> generator;
    };

    template <>
    struct generator<float>::impl {
        std::random_device source;
        std::uniform_real_distribution<float> generator;
    };

    template <typename T>
    generator<T>::~generator() noexcept {
        delete pimpl;
    }

    template <typename T>
    generator<T>::generator() {
        pimpl = new impl();
    }

    template <typename T>
    generator<T>::generator(generator&& other) noexcept {
        pimpl = core::exchange(other.pimpl, nullptr);
    }

    template <typename T>
    auto generator<T>::operator()() noexcept -> T {
        return pimpl->generator(pimpl->source);
    }

    template <typename T>
    auto generator<T>::operator=(generator&& other) noexcept -> generator& {
        generator(core::move(other)).swap(*this);
        return *this;
    }

    template <typename T>
    auto generator<T>::swap(generator& other) noexcept -> void {
        using test::swap;
        swap(*this, other);
    }

    template <typename T>
    auto swap(range<T>& left, range<T>& right) noexcept -> void {
        auto buffer = left.buffer;
        auto buffer_size = left.buffer_size;
        left.buffer = right.buffer;
        left.buffer_size = right.buffer_size;
        right.buffer = buffer;
        right.buffer_size = buffer_size;
    }

    template <typename T>
    auto swap(generator<T>& left, generator<T>& right) noexcept -> void {
        auto pimpl = left.pimpl;
        left.pimpl = right.pimpl;
        right.pimpl = pimpl;
    }

    template class range<int>;
    template class range<float>;

    template class generator<int>;
    template class generator<float>;

    template auto swap(range<int>&, range<int>&) noexcept -> void;
    template auto swap(range<float>&, range<float>&) noexcept -> void;
    template auto swap(generator<int>&, generator<int>&) noexcept -> void;
    template auto swap(generator<float>&, generator<float>&) noexcept -> void;

}
