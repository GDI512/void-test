#include <void_test.hpp>
#include <vector>

// clang-format off

VOID_TEST_BEGIN

void_test::unit("std::vector test", [](){

    void_test::unit("constructor test", [](){

        void_test::unit("default constructor test", [](){
            auto vector = std::vector<int>();
            void_test::check_equal(vector.size(), 0U);
            void_test::check_equal(vector.capacity(), 0U);
        });

        void_test::unit("resize constructor test", [](){
            auto vector = std::vector<int>(256);
            void_test::check_equal(vector.size(), 256U);
            void_test::check_equal(vector.capacity(), 256U);
        });

        void_test::unit("copy constructor test", [](){
            auto other = std::vector<int>(256);
            auto vector = std::vector<int>(other);
            void_test::check_equal(vector.size(), 256U);
            void_test::check_equal(vector.capacity(), 256U);
        });

        void_test::unit("move constructor test", [](){
            auto other = std::vector<int>(256);
            auto vector = std::vector<int>(std::move(other));
            void_test::check_equal(vector.size(), 256U);
            void_test::check_equal(vector.capacity(), 256U);
        });

        void_test::unit("initializer list constructor test", [](){
            auto other = std::vector<int>{0, 0, 0, 0, 0, 0};
            auto vector = std::vector<int>(std::move(other));
            void_test::check_equal(vector.size(), 6U);
            void_test::check_equal(vector.capacity(), 6U);
        });

    });

    void_test::unit("modifier test", [](){

        void_test::unit("push_back test", [](){
            auto vector = std::vector<int>(100);
            vector.push_back(0);
            void_test::check_equal(vector.size(), 101U);
            void_test::check_greater(vector.capacity(), 101U);
        });

    });

});

VOID_TEST_END

// clang-format on
