#include <scope.hpp>
#include <output.hpp>

namespace void_test::core {

    scope::scope(string name) noexcept : name(name) {
        output::on_scope(name);
    }

    auto scope::data() noexcept -> string {
        return current().name;
    }

}
