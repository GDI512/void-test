#ifndef VOIDTEST_TYPE_HPP
#define VOIDTEST_TYPE_HPP

namespace test {

    class object {
      private:
        volatile int value;
        volatile object* self;

      public:
        ~object() noexcept;
        object() noexcept;
        object(object&& other) noexcept;
        object(const object& other) noexcept;

      public:
        auto operator=(object&& other) noexcept -> object&;
        auto operator=(const object& other) noexcept -> object&;

      private:
        auto is_self() const noexcept -> bool;
        auto is_initialized() const noexcept -> bool;
        auto is_uninitialized() const noexcept -> bool;
    };

    auto operator==(const object& left, const object& right) noexcept -> bool;
    auto operator!=(const object& left, const object& right) noexcept -> bool;

}

#endif
