#include <iostream>

struct WithMutable {
    int var = 0;
    const int var_const = 0;
    mutable int var_mut = 0;
    // mutable int& y;


    void modify() {
        var = var + 1;
        var_mut = var_mut + 1;
        // var_const = var_const + 1; //ERROR
    }

    void modify_mutable() const {
        var_mut = var_mut + 1;
        // var = var + 1; //ERROR
        // var_const = var_const + 1; //ERROR
    }
};

int main() {
    {
        WithMutable not_const;
        not_const.modify();
    }
    {
        const WithMutable m_const;
        // m_const.modify(); //ERROR
        m_const.var_mut = m_const.var_mut + 1;
        std::cout << m_const.var_mut << std::endl;
    }
    {
        const auto print = [](const char* str, int x, int y) {
            std::cout << str << ": " << x << " " << y << '\n';
        };
        int x = 1, y = 1;
        print("in main()", x, y);
        auto foo = [x, y, &print]() mutable {
            ++x;
            ++y;
            print("in foo()", x, y);
        };
        foo();
        print("in main()", x, y);
    }

    // https://cppinsights.io/s/82db5f45
}