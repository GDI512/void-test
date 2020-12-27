#include <void_test.hpp>
#include <vector>

// clang-format off

int main() {

    test::unit("std::vector test", [](){

        test::unit("constructor test", [](){

            test::unit("default constructor test", [](){
                auto vector = std::vector<int>();
                test::assert_equal(vector.size(), 0U);
                test::assert_equal(vector.capacity(), 0U);
            });

            test::unit("resize constructor test", [](){
                auto vector = std::vector<int>(256);
                test::assert_equal(vector.size(), 256U);
                test::assert_equal(vector.capacity(), 256U);
            });

            test::unit("copy constructor test", [](){
                auto other = std::vector<int>(256);
                auto vector = std::vector<int>(other);
                test::assert_equal(vector.size(), 256U);
                test::assert_equal(vector.capacity(), 256U);
            });

            test::unit("move constructor test", [](){
                auto other = std::vector<int>(256);
                auto vector = std::vector<int>(std::move(other));
                test::assert_equal(vector.size(), 256U);
                test::assert_equal(vector.capacity(), 256U);
            });

            test::unit("initializer list constructor test", [](){
                auto other = std::vector<int>{0, 0, 0, 0, 0, 0};
                auto vector = std::vector<int>(std::move(other));
                test::assert_equal(vector.size(), 6U);
                test::assert_equal(vector.capacity(), 6U);
            });

        });

        test::unit("modifier test", [](){

            test::unit("push_back test", [](){
                auto vector = std::vector<int>(100);
                vector.push_back(0);
                test::assert_equal(vector.size(), 101U);
                test::assert_greater(vector.capacity(), 101U);
            });

        });

    });

    return test::status();

}

// clang-format on
