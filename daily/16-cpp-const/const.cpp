#include <iostream>
struct Simple {
    int i;
    const int b;

    Simple(int a): b(a) {
        i = 42;
        // b = 2; // ERROR
    };

    void modify(int f) {
        i = 32;
        /*b = 2 */ // ERROR
    }

    void print() const {
        // i = 32; //Error
        // b = 2;  // ERROR
        std::cout << "print() i: " << i << ", " << b << std::endl;
    }

    void const_argument(const int arg) {
        i = i + arg;
        /*b = 2 */ // ERROR
        /*arg = 2 */ // ERROR
    }

};

struct CopyArgs {
    int sum(int a, int b) {
        return a + b;
    }
    // int sum(const int a, const int b) { return a + b }
    // const int sum(const int a, const int b) { return a + b }
};

struct RefArgs {
    int sum(int& a, int& b) {
        std::cout << "RefArgs: int sum(int& a, int& b)" << std::endl;
        return a + b;
    }
    int sum(const int& a, const int& b) {
        std::cout << "RefArgs: int sum(const int& a, const int& b)" << std::endl;
        return a + b;
    }
};

struct ConstSpecifier {
    int sum(int a, int b) {
        std::cout << "ConstSpecifier: int sum(int a, int b)" << std::endl;
        return a + b;
    }
    int sum(int a, int b) const {
        std::cout << "ConstSpecifier: int sum(int a, int b) const" << std::endl;
        return a + b;
    }
};

int main(int argc, char **) {
    std::cout << "1 ------------------\n";
    {
        int a = 5;
        const int b = 10;
        a = 3;
        // b = 4; FAIL
        Simple s(22);
        s.modify(42);
        s.print();
        s.const_argument(a);
    }
    std::cout << "2 ------------------\n";
    {
        CopyArgs ca;
        ca.sum(1, 2);
        std::cout << ca.sum(1, 2) << std::endl;
    }
    std::cout << "3 ------------------\n";
    {
        int a = 0;
        int b = 0;
        RefArgs ra;
        ra.sum(a, b);
        const int a_const = 0;
        const int b_const = 0;
        ra.sum(a_const, b_const);
        ra.sum(a,       b_const);
        ra.sum(a, const_cast<const int&>(b));
    }
    std::cout << "4 ------------------\n";
    {
        ConstSpecifier cs;
        cs.sum(1, 2);
        const ConstSpecifier const_cs;
        const_cs.sum(1, 2);
    }
    std::cout << "5 ------------------\n";
    {
        using F = int(int);
        using F_CONST_ARG = int(const int);
        using F_CONST_RET= const int(int);

        std::cout << std::boolalpha << std::is_same_v<int, const int> << std::endl;
        std::cout << std::boolalpha << std::is_same_v<int&, const int&> << std::endl;
        /*
        cppreference: After producing the list of parameter types,
        any top-level cv-qualifiers modifying a parameter type are
        deleted when forming the function type.
         */
        std::cout << std::boolalpha << std::is_same_v<F, F_CONST_ARG> << std::endl;
        std::cout << std::boolalpha << std::is_same_v<F, F_CONST_RET> << std::endl;
    }
    std::cout << "6 ------------------\n";
    {
        int var, var2;
        const int const_var = 0;
        //const int& const_ref = var;
        int const& const_ref = var;

        const int& const_ref2 = const_var;
        // int& const s = i; ERROR

        int* ptr = &var;
        *ptr = 32;
        ptr = &var2;
        //int* ptr = &const_var; // ERROR

        const int* ptr_to_const_int = &var;
        //*ptr_to_const_int = 44; // ERROR
        ptr_to_const_int = &var2;

        int* const const_ptr_to_int = &var;
        *const_ptr_to_int = 22;
        // const_ptr_to_int = &var2; // ERROR

        const int* const const_ptr_to_const_int = &const_var;
        // *const_ptr_to_const_int = 22; ERROR
        // const_ptr_to_const_int = &var2; // ERROR
    }

}
