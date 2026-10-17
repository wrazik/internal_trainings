/* PRE-CPP 11 */
#include <iostream>

constexpr int sum_until(int num) {
    if (num < 0) {
        throw std::range_error("negative exponent for integer power");
    }
    int sum = 0;
    for (int i = 0; i <= num; ++i) {
        sum += i;
    }
    return sum;
}

int main(int argc, char **) {
    static_assert(sum_until(20) == 210);
    std::cout << sum_until(argc) << "\n";
}