#ifndef VOID_TEST_RESOURCE_HPP
#define VOID_TEST_RESOURCE_HPP

namespace test {

    class resource {
      private:
        int value;
        resource* self;

      public:
        ~resource() noexcept;
        resource(int value = 0) noexcept;
        resource(resource&& other) noexcept;
        resource(const resource& other) noexcept;

      public:
        operator int() const noexcept;
        operator int&() noexcept;
        auto operator=(resource&& other) noexcept -> resource&;
        auto operator=(const resource& other) noexcept -> resource&;
    };

}

#endif
