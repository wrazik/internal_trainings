#include <print>

struct DelegatingConstructor {
    DelegatingConstructor(int xx, int yy): y{2}, x{y + 2}  { }
    DelegatingConstructor(int x): DelegatingConstructor(x, 0) {}
    DelegatingConstructor(): DelegatingConstructor(0, 0) {}

    int x;
    int y;
};


int main() {
    DelegatingConstructor d1;
    DelegatingConstructor d2 = 2;
    DelegatingConstructor d3 = {2, 4};
    DelegatingConstructor d4 {2, 4};
    DelegatingConstructor d5 (2, 4);
}