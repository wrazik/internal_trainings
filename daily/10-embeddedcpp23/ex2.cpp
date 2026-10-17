#include <array>
#include <memory>
#include <string_view>
#include <type_traits>
#include <utility>
#include <iostream>

#include <string>
#include <cstdlib>
#include <cxxabi.h>

template<typename T>
std::string type_name()
{
    int status;
    std::string tname = typeid(T).name();
    char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
    if(status == 0) {
        tname = demangled_name;
        std::free(demangled_name);
    }
    return tname;
}

int main()
{
    const int old_c_style_array[32] = {};
    const auto new_std_array = std::to_array(old_c_style_array); // C++20
    static_assert(std::is_same_v<decltype(new_std_array), const std::array<int, 32>>);

    const auto a2 = std::array{"foo"};
    static_assert(std::is_same_v<decltype(a2), const std::array<const char*, 1>>);

    const auto str = "Hello world";
//    const auto const_char_var = std::to_array(str); // TODO: doesn't work
    const auto const_char_var = std::to_array("Helo world");

    const char arr[] = "Hello world";
    const auto const_char_arr = std::to_array(arr);
    const auto const_char_literal = std::to_array("Hello world"); // C++20

    std::cout << type_name<decltype(str)>() << "\n";
    std::cout << type_name<decltype(arr)>() << "\n";
    std::cout << type_name<decltype("Hello world")>() << "\n";
}