#include <iostream>
struct Config {
    static constexpr int max_size = 2137;
};

void print(const int& value) {
    std::cout << value << "\n";
}

int main(int argc, char **) {
    constexpr int a = Config::max_size;
    static_assert(Config::max_size == 2137);
    print(Config::max_size);
}