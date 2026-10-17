#include <iostream>
#include <print>

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

struct LightBulbControl {
    MacAddr bulbAddress;
    RgbColor color;
    uint16_t brightness;
};

static_assert(std::has_unique_object_representations_v<LightBulbControl>); // c++17

class Bulb {
    RgbColor color{};
    uint16_t brightness{};

public:
    constexpr Bulb(const RgbColor cl, const uint16_t br) {Update(cl, br);}

    constexpr void Update(const RgbColor cl, const uint16_t br) {
        if not consteval {  // C++23
            std::println("Bulb is at brightness: {}", br); // C++23
        }
        color = cl;
        brightness = br;
    }
};

constinit Bulb ceiling{{}, 23}; // C++20

FP16 toFP16(float f) {
    const uint32_t bits(*reinterpret_cast<uint32_t*>(&f)); // UB!
    const uint32_t sign{(bits >> 16u) & 0x8000u};
    const uint32_t exp{((bits >> 23u) & 0xFFu) - 127u + 15u};
    const uint32_t mant{(bits & 0x7FFFFU) >> 13u};
    if (exp <= 0) { return {static_cast<uint16_t>(sign)};}
    if (exp >= 0x1Fu) { return {static_cast<uint16_t>(sign | 0x7C00u)};}

    return {static_cast<uint16_t>(sign | (exp << 10u) | mant)};
}

FP16 toFP16WithUnion(float f) {
    union FloarOrInt {
        float f;
        uint32_t v;
    };
    const uint32_t bits(FloarOrInt{f}.v); // UB
    const uint32_t sign{(bits >> 16u) & 0x8000u};
    const uint32_t exp{((bits >> 23u) & 0xFFu) - 127u + 15u};
    const uint32_t mant{(bits & 0x7FFFFU) >> 13u};
    if (exp <= 0) { return {static_cast<uint16_t>(sign)};}
    if (exp >= 0x1Fu) { return {static_cast<uint16_t>(sign | 0x7C00u)};}

    return {static_cast<uint16_t>(sign | (exp << 10u) | mant)};
}

FP16 toFP16Correct(float f) {
    const uint32_t bits(std::bit_cast<uint32_t>(f)); // C++ 20
    const uint32_t sign{(bits >> 16u) & 0x8000u};
    const uint32_t exp{((bits >> 23u) & 0xFFu) - 127u + 15u};
    const uint32_t mant{(bits & 0x7FFFFU) >> 13u};
    if (exp <= 0) { return {static_cast<uint16_t>(sign)};}
    if (exp >= 0x1Fu) { return {static_cast<uint16_t>(sign | 0x7C00u)};}

    return {static_cast<uint16_t>(sign | (exp << 10u) | mant)};
}

int main() {
    ceiling.Update({1, 2, 3}, 23);
}