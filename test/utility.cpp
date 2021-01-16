// ============================================================================
//  Test file for utility functions and classes
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <utility>
#include <type_traits>

using namespace void_test::core;

int main() {
    {
        static_assert(std::is_same_v<int, remove_reference<int>::type>);
        static_assert(std::is_same_v<int, remove_reference<int&>::type>);
        static_assert(std::is_same_v<int, remove_reference<int&&>::type>);
    }
    {
        static_assert(is_lvalue_reference<int&>::value);
        static_assert(!is_lvalue_reference<int>::value);
        static_assert(!is_lvalue_reference<int&&>::value);
    }
    {
        auto value = 4;
        auto rvalue = [](int x) -> int { return x; };
        auto lvalue = [](int& x) -> int& { return x; };
        static_assert(std::is_same_v<int&&, decltype(std::forward<int>(lvalue(value)))>);
        static_assert(std::is_same_v<int&&, decltype(std::forward<int>(rvalue(value)))>);
    }
    {
        struct type : static_list<type> {};
        auto object = type();
        assert(&type::current() == &object);
        auto other = type();
        assert(&type::current() == &other);
        {
            auto nested = type();
            assert(&type::current() == &nested);
        }
        assert(&type::current() == &other);
    }
}
