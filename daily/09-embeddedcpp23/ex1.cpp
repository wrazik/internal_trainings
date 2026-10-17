#include <cstdint>
#include <type_traits>
#include <iostream>

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

int main() {
    std::cout << sizeof(likely_padded);
}