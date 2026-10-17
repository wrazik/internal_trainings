/* Opus magnum - std::from_chars

std::from_chars_result from_chars(const char* first,
                                  const char* last,
                                  FLOAT_TYPE& value,
                                  std::chars_format fmt = std::chars_format::general);

std::from_chars_result from_chars(const char* first,
                                  const char* last,
                                  TYPE &value,
                                  int base = 10);
*/

#include <charconv> // from_char, to_char
#include <string>
#include <iostream>

constexpr std::optional<int> to_int(std::string_view sv)
{
    int value {};
    const auto ret = std::from_chars(sv.begin(), sv.end(), value);
    if (ret.ec == std::errc{})
        return value;

    return {};
};

int main() {
    const std::string str { "343.3twojastara" };
    double value = 0;
    const auto res = std::from_chars(str.data(),
                                 str.data() + str.size(),
                                 value);

    if (res.ec == std::errc())
    {
        std::cout << "value: " << value
                  << ", parsed count: " << res.ptr - str.data() << '\n';
    }
    else if (res.ec == std::errc::invalid_argument)
    {
        std::cout << "invalid argument!\n";
    }
    else if (res.ec == std::errc::result_out_of_range)
    {
        std::cout << "out of range! res.ptr distance: "
                  << res.ptr - str.data() << '\n';
    }

    static_assert(to_int("hello") == std::nullopt);
    static_assert(to_int("10") == 10);
}

