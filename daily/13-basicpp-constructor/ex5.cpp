#include <string>
#include <print>


struct Product {
    Product() : name{"default product"}, value{} { }
    /* explicit */ Product(float v) : name{"basic"}, value{v} { }
    /* explicit */ Product(const std::string& n, int v) : name{n}, value{v} { }
    std::string name;
    int value;
};

void printProduct(const Product& prod) {
    std::println("{}, {}", prod.name, prod.value);
}

int main() {
    Product numbers(100.2); // copy initialization
    Product box = {"a box", 1}; // copy list-initialization

    printProduct(numbers);
    printProduct(box);

    printProduct(Product(1.2));
    printProduct(Product("1 a box", 1));

//    printProduct(Product{2.1}); // not compiling
    printProduct(Product{2});
    printProduct(Product{"2 a box", 2});

//    printProduct({3.2}); // not compiling
    printProduct({3});
    printProduct({"3 a box", 3});
}
