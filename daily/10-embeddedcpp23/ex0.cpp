#include <iostream>
#include <print>
#include <string_view>
#include <expected>
#include <string>
#include <memory>

struct MacAddr {
    std::array<unsigned char, 6> data;
};

struct FP16 {
    uint16_t value;
};

struct RgbColor {
    FP16 r;
    FP16 g;
    FP16 b;
    FP16 a;
};

enum class Protocol: uint8_t {
    Update,
};


enum class ColorParts {Red, Green, Blue, Alpha };

constexpr auto getNameOld(ColorParts idx) {
    constexpr std::array<std::string_view, 4> data {"Red", "Green", "Blue", "Alpha"};
    return data.at(static_cast<std::underlying_type_t<ColorParts>>(idx));
}

constexpr auto getName(ColorParts idx) {
    static constexpr std::array<std::string_view, 4> data {"Red", "Green", "Blue", "Alpha"}; // C++23
    return data.at(static_cast<std::underlying_type_t<ColorParts>>(idx));
}

constexpr bool isAllowedHexChar(char c) {
    return (c >= '0' && c <= '9') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

constexpr std::expected<MacAddr, std::errc> macFromString(std::span<const char> addr) {
    if (addr.size() < 17) {
        return std::unexpected(std::errc::message_size);
    }

    MacAddr res{};

    for(size_t i = 0; auto& val: res.data) {
        if (i < 5 && addr[2] != ':') {
            return std::unexpected(std::errc::message_size);
        }
        if (!(isAllowedHexChar(addr[0]) && isAllowedHexChar(addr[1]))) {
            return std::unexpected(std::errc::invalid_argument);
        }
        if(std::from_chars(addr.data(), addr.data() + 2, val, 16).ec!= std::errc()) { // constexpr in C++23
            return std::unexpected(std::errc::message_size);
        }
        addr = addr.subspan((addr.size() >= 3) ? 3 : addr.size());
        ++i;
    }
    return res;
}

consteval MacAddr operator ""_mac(const char* str, size_t length) { // C++20
    return macFromString({str, length}).value();
}

void mac() {
    auto data {std::to_array("12:34:56:78:90:AB")}; // c-string literal into struct, c++20
    auto m = macFromString(data);

    constexpr auto compileTimeMac = "12:34:56:78:90:AB"_mac;
    static_assert(compileTimeMac.data[0] == 0x12);
    static_assert(compileTimeMac.data[1] == 0x34);
    static_assert(compileTimeMac.data[2] == 0x56);
    static_assert(compileTimeMac.data[3] == 0x78);
    static_assert(compileTimeMac.data[4] == 0x90);
    static_assert(compileTimeMac.data[5] == 0xAB);
}

int main() {
    mac();
    std::cout << getName(ColorParts::Blue) << std::endl;
}