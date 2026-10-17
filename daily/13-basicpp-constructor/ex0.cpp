#include <print>

struct Foo {
    int _val;

    Foo(int val): _val(val) { std::println("Foo(): {}", _val) ;}
    Foo(const Foo& f): _val(f._val) { std::println("Foo(const Foo&): {}", _val) ;}
    Foo(Foo&& f): _val(std::move(f._val)) { std::println("Foo(Foo &&): {}", _val) ;}
    Foo &operator=(const Foo &f) { _val = f._val; std::println("Foo& operator=(const Foo&): {}", _val); return *this;}
    Foo &operator=(Foo&& f) { _val = std::move(f._val); std::println("Foo& operator=(Foo f&&): {}", _val); return *this;}
    ~Foo() { std::println("~Foo(): {}", _val);}
};

int main() {
    std::println("Hello world");
    {
        // Contructor
        Foo f(1);
        Foo f1 = 2;
    }
    std::println("---------");
    {
        // Copy constructors
        Foo f(2);
        Foo f1(f);
        Foo f2 = f;
    }
    std::println("---------");
    {
        // Move constructors
        Foo f(3);
        Foo f1 (std::move(f));
        Foo ff(33);
        Foo f2 = std::move(ff);
    }
    std::println("---------");
    {
        // Copy assignment
        Foo f1(1);
        Foo f2(2);
        f1 = f2;
    }
    std::println("---------");
    {
        // Move assignment
        Foo f1(1);
        Foo f2(2);
        f1 = std::move(f2);
    }
}