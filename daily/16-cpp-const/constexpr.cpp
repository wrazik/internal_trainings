#include <iostream>

constexpr int sum(int a, int b, int c) {
    return a + b + c;
}

constexpr int pow_helper(int a, int n, int sqrt) {
    return sqrt * sqrt * ((n % 2) ? a : 1);
}

constexpr int pow(int a, int n){
    return (n < 0)
               ? throw std::range_error("negative exponent for integer power")
               : (n == 0)
                     ? 1
                     : pow_helper(a, n, pow(a, n / 2));
}

int main(int argc, char **) {
    static_assert(sum(1, 2, 3) == 6);

    static_assert(pow(2,4) == 16);
    std::cout << sum(argc, 2, 3) << std::endl;
    std::cout << pow(argc, 4) << std::endl;
}