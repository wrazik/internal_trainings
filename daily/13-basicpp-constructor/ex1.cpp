#include <print>
#include <string>
#include <map>

// Rule of 0: avoid defining default operation

// https://cppinsights.io/
struct Named_map {
public:
    explicit Named_map(const std::string& n) : name(n) {}
    // no copy/move constructors
    // no copy/move assignment operators
    // no destructor
private:
    std::string name;
    std::map<int, int> rep;
};

Named_map nm("map"); // construct
Named_map nm2 {nm};  // copy construct

// Rule of 5:
// if you define or =delete any copy, move, or destructor function, define or =delete them all

struct RAII_Example {
    RAII_Example() : ptr(new int()) { }
    int *ptr{nullptr};

    // Rule of 5:
    RAII_Example(const RAII_Example &) = delete;
    RAII_Example& operator=(const RAII_Example &) = delete;

    RAII_Example(RAII_Example &&) = delete;
    RAII_Example& operator=(RAII_Example &&) = delete;
    ~RAII_Example() { delete ptr; }

//    RAII_Example(const RAII_Example &) = default;
//    RAII_Example& operator=(const RAII_Example &) = default;

};

RAII_Example r1;
//    RAII_Example r2(r1);
//    RAII_Example r3;
//    r1 = r3;

int main() {
}
