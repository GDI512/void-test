#include <utility.hpp>
#include <state.hpp>
#include <atomic>

namespace void_test::core {

    template <typename type>
    static_list<type>* static_list<type>::active = nullptr;

    template <typename type>
    static_list<type>::~static_list() noexcept {
        active = previous;
    }

    template <typename type>
    static_list<type>::static_list() noexcept {
        previous = active;
        active = this;
    }

    template <typename type>
    auto static_list<type>::current() noexcept -> type& {
        return static_cast<type&>(*active);
    }

    template class static_list<scope>;
    template class static_list<registry>;
    template class static_list<verifier>;

    struct atomic_counter::impl {
        std::atomic_int count;
    };

    atomic_counter::~atomic_counter() {
        delete pimpl;
    }

    atomic_counter::atomic_counter() {
        pimpl = new impl();
    }

    atomic_counter::operator int() const noexcept {
        return pimpl->count;
    }

    auto atomic_counter::operator++(int) noexcept -> int {
        return pimpl->count++;
    }

    auto atomic_counter::operator--(int) noexcept -> int {
        return pimpl->count--;
    }

}
