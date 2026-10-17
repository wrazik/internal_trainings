/* PRE-CPP 11 */
#include <iostream>
#include <utility>

struct MemberAccessExample {
    MemberAccessExample():  s(0) {}

    int & get_s() { return s;};
    const int& get_s() const { return s;};

private:
    int s;
};

int main(int argc, char **) {
    MemberAccessExample mae_not_const;
    const MemberAccessExample mae_const;

    mae_not_const.get_s() = 1;
    std::cout << mae_not_const.get_s() << ", " << mae_const.get_s() << "\n";
}