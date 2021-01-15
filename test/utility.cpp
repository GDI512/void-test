// ============================================================================
//  Content:
//      Test file for utility functions and classes
//  Tests:
//      1. Test the remove_reference type trait
//      2. Test the is_lvalue_reference type trait
//      3. Test the forward function
//      4. Check if static_list objects are being linked with each other
//      5. Test the poor man's std::function
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
    { // 1.
        static_assert(std::is_same_v<int, remove_reference<int>::type>);
        static_assert(std::is_same_v<int, remove_reference<int&>::type>);
        static_assert(std::is_same_v<int, remove_reference<int&&>::type>);
    }
    { // 2.
        static_assert(is_lvalue_reference<int&>::value);
        static_assert(!is_lvalue_reference<int>::value);
        static_assert(!is_lvalue_reference<int&&>::value);
    }
    { // 3.
        auto value = 4;
        auto rvalue = [](int x) -> int { return x; };
        auto lvalue = [](int& x) -> int& { return x; };
        static_assert(std::is_same_v<int&&, decltype(std::forward<int>(lvalue(value)))>);
        static_assert(std::is_same_v<int&&, decltype(std::forward<int>(rvalue(value)))>);
    }
    { // 4.
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
    { // 5.
        struct add {
            auto operator()(float x, float y) {
                return x + y;
            }
        };
        struct functor {
            auto operator()(int x) {
                return x;
            }
        };
        auto f = function<int(int)>(functor());
        auto g = function<int(int)>([](int x) { return x; });
        auto h = function<float(float, float)>(add());
        auto j = function<float(float, float)>([](float x, float y) { return x + y; });
        assert(f(16) == 16);
        assert(g(16) == 16);
        assert(h(0.5f, 0.5f) == 1.0f);
        assert(j(0.5f, 0.5f) == 1.0f);
    }
}
