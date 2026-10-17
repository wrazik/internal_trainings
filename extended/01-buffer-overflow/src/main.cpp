#include <cstring>
#include <print>

int main(int argc, char** argv) {
    char buf[256];
    std::println("{:p}", static_cast<void*>(&buf));

    std::strcpy(buf, argv[1]);
    return 0;
}