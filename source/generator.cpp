#include <generator.hpp>
#include <random>

namespace test {

    template <typename T>
    array<T>::~array() noexcept {
        delete[] buffer;
    }

    template <typename T>
    array<T>::array() noexcept : buffer(), buffer_size() {}

    template <typename T>
    array<T>::array(size_type size, value_type value) {
        auto memory = new value_type[size];
        for (auto i = 0u; i < size; i++) {
            memory[i] = value;
        }
        buffer = memory;
        buffer_size = size;
    }

    template <typename T>
    array<T>::array(const_iterator first, const_iterator last) {
        auto size = last - first;
        auto memory = new value_type[size];
        for (auto i = 0; i < size; i++) {
            memory[i] = first[i];
        }
        buffer = memory;
        buffer_size = size;
    }

    template <typename T>
    array<T>::array(array&& other) noexcept {
        buffer = core::exchange(other.buffer, nullptr);
        buffer_size = core::exchange(other.buffer_size, 0u);
    }

    template <typename T>
    array<T>::array(const array& other) {
        auto memory = new value_type[other.size()];
        for (auto i = 0u; i < other.size(); i++) {
            memory[i] = other[i];
        }
        buffer = memory;
        buffer_size = other.size();
    }

    template <typename T>
    auto array<T>::operator=(array&& other) noexcept -> array& {
        array(core::move(other)).swap(*this);
        return *this;
    }

    template <typename T>
    auto array<T>::operator=(const array& other) -> array& {
        array(other).swap(*this);
        return *this;
    }

    template <typename T>
    auto array<T>::operator[](size_type index) noexcept -> reference {
        return buffer[index];
    }

    template <typename T>
    auto array<T>::operator[](size_type index) const noexcept -> const_reference {
        return buffer[index];
    }

    template <typename T>
    auto array<T>::swap(array& other) noexcept -> void {
        using test::swap;
        swap(*this, other);
    }

    template <typename T>
    auto array<T>::data() noexcept -> pointer {
        return buffer;
    }

    template <typename T>
    auto array<T>::data() const noexcept -> pointer {
        return buffer;
    }

    template <typename T>
    auto array<T>::front() noexcept -> reference {
        return *buffer;
    }

    template <typename T>
    auto array<T>::front() const noexcept -> const_reference {
        return *buffer;
    }

    template <typename T>
    auto array<T>::back() noexcept -> reference {
        return *(buffer + buffer_size - 1);
    }

    template <typename T>
    auto array<T>::back() const noexcept -> const_reference {
        return *(buffer + buffer_size - 1);
    }

    template <typename T>
    auto array<T>::begin() noexcept -> iterator {
        return buffer;
    }

    template <typename T>
    auto array<T>::begin() const noexcept -> const_iterator {
        return buffer;
    }

    template <typename T>
    auto array<T>::end() noexcept -> iterator {
        return buffer + buffer_size;
    }

    template <typename T>
    auto array<T>::end() const noexcept -> const_iterator {
        return buffer + buffer_size;
    }

    template <typename T>
    auto array<T>::empty() const noexcept -> bool {
        return buffer_size == 0;
    }

    template <typename T>
    auto array<T>::size() const noexcept -> size_type {
        return buffer_size;
    }

    template <typename T>
    auto array<T>::capacity() const noexcept -> size_type {
        return buffer_size;
    }

    template <typename T>
    auto array<T>::random(size_type size, int min, int max) -> array<int> {
        auto source = generator<int>();
        auto sequence = array<int>(size);
        for (auto& item : sequence) {
            item = source() % (max - min + 1) + min;
        }
        return sequence;
    }

    template <typename T>
    auto array<T>::random(size_type size, float min, float max) -> array<float> {
        auto source = generator<float>();
        auto sequence = array<float>(size);
        for (auto& item : sequence) {
            item = source() * (max - min) + min;
        }
        return sequence;
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
    auto swap(array<T>& left, array<T>& right) noexcept -> void {
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

    template class array<int>;
    template class array<float>;

    template class generator<int>;
    template class generator<float>;

    template auto swap(array<int>&, array<int>&) noexcept -> void;
    template auto swap(array<float>&, array<float>&) noexcept -> void;
    template auto swap(generator<int>&, generator<int>&) noexcept -> void;
    template auto swap(generator<float>&, generator<float>&) noexcept -> void;

}
