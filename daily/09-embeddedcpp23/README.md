# Embedded-related features of C++17/20/23

In this folder you will find few C++ features, that are really helpful in devloping software for embedded devices:

1. Checking if structure contains padding fields with std::has_unique_object_representations_v available in C++17
```cpp
struct unpadded
{
    std::uint32_t a, b;
};

struct likely_padded
{
    std::uint8_t a;
    std::uint32_t b;
};

static_assert(std::has_unique_object_representations_v<unpadded>);
static_assert(!std::has_unique_object_representations_v<likely_padded>);
```
2. std::println - nice way of logging, similar to other languages:
```cpp
std::println("Bulb is at brightness: {}", br); // C++23
```
3. consteval if statement - evaluated at compile time:
```cpp
constexpr void Update(const RgbColor cl, const uint16_t br) {
    if not consteval {  // C++23
        std::println("Bulb is at brightness: {}", br); // C++23
    }
    color = cl;
    brightness = br;
}
```

4. constinit variables (static & thread storage duration) - compile-time initialization of non-const objects
```cpp
constinit Bulb ceiling{{}, 23}; // C++20
```

5. converting 32-bit floats to uint32_t without union/reinterpret casts, using std::bit_cast:
```cpp
FP16 toFP16Correct(float f) {
    const uint32_t bits(std::bit_cast<uint32_t>(f)); // C++ 20
    const uint32_t sign{(bits >> 16u) & 0x8000u};
    const uint32_t exp{((bits >> 23u) & 0xFFu) - 127u + 15u};
    const uint32_t mant{(bits & 0x7FFFFU) >> 13u};
    if (exp <= 0) { return {static_cast<uint16_t>(sign)};}
    if (exp >= 0x1Fu) { return {static_cast<uint16_t>(sign | 0x7C00u)};}

    return {static_cast<uint16_t>(sign | (exp << 10u) | mant)};
}
```
