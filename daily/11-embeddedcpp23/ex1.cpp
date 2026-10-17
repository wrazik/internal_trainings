#include <iostream>
#include <print>
#include <vector>
#include <span>
#include <map>

void process_raw_array(int* arr, std::size_t size) {
    for(std::size_t i = 0; i < size; ++i) {
        std::print("{}, ", arr[i]);
    }
    std::println("");
}

void process_span(std::span<const int> arr) {
    for (auto i: arr) {
        std::print("{}, ", i);
    }
    std::println("");
}

void example1() {
    std::println("Example 1");
    int arr[] = {2, 4, 6, 8, 10};
    std::vector v { 1, 3, 5, 7, 9};

    process_raw_array(arr,      std::size(arr));
    process_raw_array(v.data(), std::size(v));

    process_span(arr);
    process_span(v);
}

void example2() {
    std::println("Example 2");

    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::span<int, 5> arr_span {arr};
    std::span<int> other_span {arr};
    std::span<int> vec_span{vec};

    std::cout << std::format("sizeof arr_span: {}\n", sizeof(arr_span));
    std::cout << std::format("sizeof other_span: {}\n", sizeof(other_span));
    std::cout << std::format("sizeof vec_span: {}\n", sizeof(vec_span));
}

void example3() {
    std::vector vec = {1, 2, 3};
    // from iterator & size
    std::span from_iterator_and_size(vec.begin(), /*count*/2); // 1, 2
    std::span from_iterator_and_size2(vec.begin(), /*count*/3); // 1, 2, 3

    // from iterator
    std::span from_iterator_and_end(vec.begin(), vec.end());

    //from array
    std::array<int, 3> std_arr = {1, 2, 3};
    std::span<int, 3> from_std_array(std_arr);
    std::span from_std_array2(std_arr);

    const std::array<int, 3> const_std_arr = {1, 2, 3};
    std::span<const int> from_const_std_array(const_std_arr);
}
void printSpan(std::span<const int> sp) {
    for (auto&& elem : sp)
        std::cout << elem << ' ';
    std::cout << '\n';
}

void example4() {
    std::println("Example 4");
    int arr[] = {1, 2, 3, 4, 5, 6};
    std::span sp(arr, 6);

    // subspan(start, count):
    std::span sub = sp.subspan(2, /*count*/2);
    printSpan(sub);

    // fist(count):
    std::span subFirst3 = sp.first(3);
    printSpan(subFirst3);

    // last(count):
    std::span subLast4 = sp.last(4);
    printSpan(subLast4);
}

class ConfigManager {
private:
    std::map<std::string, std::vector<uint8_t>> configs;

public:
    ConfigManager() {
        configs["database"] = {
                'h','o','s','t','=','l','o','c','a','l','h','o','s','t',';',
                'p','o','r','t','=','5','4','3','2'
        };
    }

    std::span<const uint8_t> getConfig(const std::string& name) const {
        auto it = configs.find(name);
        if (it != configs.end())
            return it->second;
        return {};
    }
};

void example5() {
    std::println("Example 5");

    ConfigManager manager;
    auto dbConfig = manager.getConfig("database");
    for (auto byte : dbConfig)
        std::cout << static_cast<char>(byte);

    auto errCfg = manager.getConfig("error"); // not present
    for (auto byte : errCfg)
        std::cout << static_cast<char>(byte);
}

int main() {
    example1();
    example2();
    example3();
    example4();
    example5();
}


