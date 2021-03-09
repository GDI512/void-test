#ifndef CPPLTF_OUTPUT_HPP
#define CPPLTF_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test::core {

    class output {
      public:
        static size_type level;

      private:
        const registry& state;

      public:
        ~output() noexcept;
        output(string name, const registry& state) noexcept;

      public:
        static auto on_error(string source) noexcept -> void;
        static auto on_success(string source) noexcept -> void;
        static auto on_exception(string source) noexcept -> void;
    };

}

#endif
