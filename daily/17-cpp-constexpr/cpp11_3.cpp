#include <iostream>
#include <utility>

template<typename T>
void print_type() {
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

struct Foo {
    constexpr int foo() { return 42; };
};

struct A {
    constexpr A(int v) : n(v) {}
    constexpr int get_n() { return n; }
    int n;
};

struct B {
    constexpr B(int v) : a(v) {}
    constexpr const A &get_a() const { return a; }
    /*constexpr*/ A &get_a() { return a; }
    A a;
};

int main(int argc, char **) {
    print_type<decltype(&Foo::foo)>();

    /*constexpr*/ const int n = B(3).get_a().get_n();
}