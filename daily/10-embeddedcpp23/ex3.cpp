#include <expected>
#include <array>
#include <span>
#include <system_error>
#include <charconv>
#include <iostream>
#include <print>

using namespace std::string_view_literals;

struct MacAddr {
    std::array<unsigned char, 6> data;
};

constexpr bool isAllowedHexChar(char c) {
    return (c >= '0' && c <= '9') ||
           (c >= 'A' && c <= 'F') ||
           (c >= 'a' && c <= 'f');
}

constexpr std::expected<MacAddr, std::errc>
macFromString(std::span<const char> addr) {
    if (addr.size() != 17) {
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

int main(int argc, char* argv[]) {
    constexpr auto myMac = "31:23:45:69:89:90"_mac;

//    constexpr auto myMac = "01:23:45:67:89:GA"_mac;
//    constexpr auto myMac = "01:23:45:67:89:GAzz"_mac;
    for (const auto& c: myMac.data) {
        std::print("{:X}", c);
    }

    const auto runtime = std::format("{}2a:34:56:78:90:AB", argc);
    const auto macRuntime = macFromString({runtime});
    if (macRuntime) {
        for (const auto& c: macRuntime.value().data) {
            std::print("{:X} ", c);
        }
        std::print("\n"); }
    else {
        if (macRuntime.error() == std::errc::invalid_argument) {
            std::println("Not an hex character");
        }
        else if (macRuntime.error() == std::errc::message_size) {
            std::println("Message size incorrect");
        }
    }

    const auto defaultVal = macFromString("12:34:56:78:99:AG"sv).value_or(MacAddr{});
    std::println("Default value:\n");
    for (const auto& c: defaultVal.data) {
        std::print(" \n {:02X} ", c);
    }

    const auto linkedAction = macFromString("12:34:56:78:99:AB"sv)
    .and_then([](const MacAddr& mc) -> std::expected<int, std::errc> {
        std::print("And then");
        for (const auto& c: mc.data) {
            std::print("{:02X} ", c);
        }
        return {666};
    }).or_else([](std::errc e) -> std::expected<int, std::errc> {
        std::print("Error - {}", static_cast<int>(e));
        return std::unexpected(e);
    });

}