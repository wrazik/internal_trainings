#include <array>
#include <cstdint>
#include <cstring>
#include <expected>
#include <print>
#include <span>
#include <string_view>

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

enum class Protocol : uint8_t {
    Update,
};

struct LightBulbControl {
    MacAddr bulbAdress;
    RgbColor color;
    uint16_t brightness;
};

enum class ColorParts { Red, Green, Blue, Alpha };

template <typename T>
[[nodiscard]] T* start_lifetime_as(void* mem) noexcept {
    auto bytes = new (mem) unsigned char[sizeof(T)];
    auto ptr   = reinterpret_cast<T*>(bytes);
    (void)*ptr;
    return ptr;
}
template <typename T>
[[nodiscard]] const T* start_lifetime_as(const void* mem) noexcept {
    const auto mp    = const_cast<void*>(mem);
    const auto bytes = new (mp) unsigned char[sizeof(T)];
    const auto ptr   = reinterpret_cast<const T*>(bytes);
    (void)*ptr;
    return ptr;
}

static void PrintMac(const MacAddr& mac) {
    std::print("  bulbAdress = ");
    for (size_t i = 0; i < mac.data.size(); ++i) {
        std::print("{:02X}", static_cast<unsigned>(mac.data[i]));
        if (i + 1 != mac.data.size()) std::print(":");
    }
    std::println("");
}

static void PrintFP16(std::string_view name, FP16 v) {
    std::println("  {} = 0x{:04X} ({})", name, static_cast<unsigned>(v.value), static_cast<unsigned>(v.value));
}

void Process(const LightBulbControl& lightBulbControl) {
    std::println("Proces...");

    PrintMac(lightBulbControl.bulbAdress);

    std::println("  color:");
    PrintFP16("    r", lightBulbControl.color.r);
    PrintFP16("    g", lightBulbControl.color.g);
    PrintFP16("    b", lightBulbControl.color.b);
    PrintFP16("    a", lightBulbControl.color.a);

    std::println("  brightness = {} (0x{:04X})",
                 static_cast<unsigned>(lightBulbControl.brightness),
                 static_cast<unsigned>(lightBulbControl.brightness));
}

void Receive(std::span<const unsigned char> data) {
    if (Protocol::Update == Protocol{data[0]}) {
        Process(*start_lifetime_as<LightBulbControl>(
                data.subspan(1, sizeof(LightBulbControl)).data()));
    }
}

int main() {
    LightBulbControl ctrl{
            .bulbAdress = MacAddr{{0xDE, 0xAD, 0xBE, 0xEF, 0x12, 0x34}},
            .color      = RgbColor{FP16{0x3C00}, FP16{0x3800}, FP16{0x0000}, FP16{0x3C00}},
            .brightness = 1023,
    };

    std::array<unsigned char, 1 + sizeof(LightBulbControl)> packet{};
    packet[0] = static_cast<unsigned char>(Protocol::Update);

    std::memcpy(packet.data() + 1, &ctrl, sizeof(ctrl)); //don't care about copy, we want ilustrate receive

    Receive(std::span<const unsigned char>(packet));
    return 0;
}
