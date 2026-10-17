#include <iostream>
constexpr int foo(int f) {
    if consteval {
        return 2;
    }
    return f*f;
}

int main(int argc, char* argv[]) {
    const int x = foo(argc);
    constexpr int y = foo(8);

    std::cout << x << std::endl;
    std::cout << y << std::endl;
}