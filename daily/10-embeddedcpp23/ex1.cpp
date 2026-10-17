#include <array>
#include <string_view>
#include <utility>
#include <iostream>

enum class ColorParts {Red, Green, Blue, Alpha };

constexpr auto getNameOld(ColorParts idx) {
    constexpr std::array<std::string_view, 4> data {"Red", "Green", "Blue", "Alpha"};
    return data.at(static_cast<std::underlying_type_t<ColorParts>>(idx));
}

constexpr auto getName(ColorParts idx) {
    static constexpr std::array<std::string_view, 4> data {"Red", "Green", "Blue", "Alpha"}; // C++23
    return data.at(std::to_underlying(idx));
}

int main(int argc, char* argv[]) {
//    static_assert(getName(ColorParts::Red) == "Red");
//    std::cout << getName(ColorParts::Red) << "\n";
//    std::cout << getName(ColorParts::Green) << "\n";
//    std::cout << getName(ColorParts::Blue) << "\n";
//    std::cout << getName(ColorParts::Alpha) << "\n";
    static_assert(getNameOld(ColorParts::Red) == "Red");
    std::cout << getNameOld(ColorParts::Red) << "\n";
    std::cout << getNameOld(ColorParts::Green) << "\n";
    std::cout << getNameOld(ColorParts::Blue) << "\n";
    std::cout << getNameOld(ColorParts::Alpha) << "\n";
}