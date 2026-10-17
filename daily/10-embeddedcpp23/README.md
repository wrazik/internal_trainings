# Embedded-related features of C++17/20/23

In this folder you will find few C++ features, that are really helpful in devloping software for embedded devices:

1. static constexpr - it is possible to have static constexpr variables:
```cpp
constexpr auto getName(ColorParts idx) {
    static constexpr std::array<std::string_view, 4> data {"Red", "Green", "Blue", "Alpha"}; // C++23
    return data.at(std::to_underlying(idx));
}
```
[LINK TO GODBOLT](https://godbolt.org/z/Paq5z6xPK)

2. std::to_underlying - convert an enumeration to its underlying_type, shorthand for static_cast<std::undierlying_type_t<Enum>>(e)
```cpp
constexpr auto getName(ColorParts idx) {
    static constexpr std::array<std::string_view, 4> data {"Red", "Green", "Blue", "Alpha"}; // C++23
    return data.at(std::to_underlying(idx));
}
```
3. consteval - forcing method to be called in compile time: 
```cpp
consteval MacAddr operator ""_mac(const char* str, size_t length) { // C++20
    return macFromString({str, length}).value();
}
```
Calling .value() on std::expected in case of lack of value will trigger throwing exception. Because throwing exception is
not yet compile-time friendly, the code will tell you at compile-time if value was parsed

3. std::to_array - converting c-style arrays to std::array
```cpp
const int old_c_style_array[32] = {};
const auto new_std_array = std::to_array(old_c_style_array); // C++20
static_assert(std::is_same_v<decltype(new_std_array), const std::array<int, 32>>);

const auto a2 = std::array{"foo"};
static_assert(std::is_same_v<decltype(a2), const std::array<const char*, 1>>);

const auto str = "Hello world";
//    const auto const_char_var = std::to_array(str); // TODO: doesn't work
const auto const_char_var = std::to_array("Helo world");
```
Note that `const char*` doesn't contain size, so type deduction can't calculate size of the literal and conversion doesn't work

3. std::expected - handling errors in a way thay can't be ignored, without the exceptions
```cpp
constexpr std::expected<MacAddr, std::errc> macFromString(std::span<const char> addr) {
    ...
}
```
std::expected can be converted to boolean:
```cpp
    const auto macRuntime = macFromString({runtime});
    if (macRuntime) {
        ...
    }
```
To get underlying error, you can call .error(). If correct value was returned, exception will be thrown.
```cpp
    else {
        if (macRuntime.error() == std::errc::invalid_argument) {
            std::println("Not an hex character");
        }
        else if (macRuntime.error() == std::errc::message_size) {
            std::println("Message size incorrect");
        }
    }
```

It is possible to set value to default if it was not created correctly:
```cpp
    const auto defaultVal = macFromString("12:34:56:78:99:AG"sv).value_or(MacAddr{});
```

You can also chain methods - using `.and_then` and `or_else` functions that are taking function pointers.
`.and_then` will be called only if all previous calls in the chain will produce correct value. `or_else` will 
be called after first returned error.
```cpp
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

```
