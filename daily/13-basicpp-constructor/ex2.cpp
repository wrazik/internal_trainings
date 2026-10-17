#include <print>

struct Foo {
    int x;
};

struct Bar {
    Bar(int x): x{x} { }
    int x;
};

int main() {
    Foo uninitialized;
    std::println("Not initialized: {}", uninitialized.x);

    Foo brace_init {};
    std::println("Initialized: {}", brace_init.x);

//    Foo incorrect1();
//    Foo incorrect2(Foo());

    Foo f2{Foo()};
    Foo f3{Foo{}};

//    Foo f3 = 32;
    Foo f4 {34};
    Foo f5 = {34};

    Bar b(21.37);
    Bar b2 = 21.37;
//    Bar b3 = {21.37};
//    Bar b4{21.37}; // error - narrowing conversion
}