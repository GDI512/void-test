#ifndef CPPLTF_FORMAT_HPP
#define CPPLTF_FORMAT_HPP

namespace test::format {

    constexpr auto space = "\040\040";
    constexpr auto scope = "(\033[93munit\033[0m %s)\n";
    constexpr auto error = "(\033[31merror\033[0m %s)\n";
    constexpr auto success = "(\033[32mok\033[0m %s)\n";
    constexpr auto exception = "(\033[31mexception\033[0m\040%s)\n";
    constexpr auto test_error = "(\033[31mtest\040error\033[0m\040[%zu/%zu])\n";
    constexpr auto test_success = "(\033[32mtest\040ok\033[0m\040[%zu/%zu])\n";
    constexpr auto resource_error = "(\033[31mresource\040error\033[0m\040[%zu/%zu]\040[%zu/%zu/%zu])\n";
    constexpr auto resource_success = "(\033[32mresource\040ok\033[0m\040[%zu/%zu]\040[%zu/%zu/%zu])\n";

}

#endif
