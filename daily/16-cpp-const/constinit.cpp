#include <iostream>

// C++11
constexpr int sum(int a, int b, int c) {
    return a + b + c;
}

int main(int argc, char **) {
    static_assert(sum(1, 2, 3) == 6);
    return 0;
}
