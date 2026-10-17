# C++17/20/23 embedded features

```cpp
void ReceivePretty(std::span<const unsigned char> data) {
    if (Protocol::Update == Protocol{data[0]}) {
        Process(*start_lifetime_as<LightBulbControl>(data.subspan(1, sizeof(LightBulbControl)).data()));
    }
}
```
## std::span
### Basic usage
Instead of using raw C-array as argument function:
```cpp
void process_raw_array(int* arr, std::size_t size) {
    for(std::size_t i = 0; i < size; ++i) {
        std::print("{}, ", arr[i]);
    }
    std::println("");
}
// . . . 
    int arr[] = {2, 4, 6, 8, 10};
    std::vector v { 1, 3, 5, 7, 9};
    process_raw_array(arr,      std::size(arr));
    process_raw_array(v.data(), std::size(v));
```
It's better to use std::span, which is wrapper around pointer and a size:

```cpp
void process_span(std::span<const int> arr) {
    // . . .
}

// . . .
std::println("Example 1");
int arr[] = {2, 4, 6, 8, 10};
std::vector v { 1, 3, 5, 7, 9};

process_span(arr);
process_span(v);
```
### Sizeof std::span
If use provides compile-time size (as non-type template parameter), std::span requires only one pointer to store the value:
```cpp
int arr[] = {1, 2, 3, 4, 5};
std::vector<int> vec = {1, 2, 3, 4, 5};

std::span<int, 5> arr_span {arr};
std::span<int> other_span {arr};
std::span<int> vec_span{vec};

std::cout << std::format("sizeof arr_span: {}\n", sizeof(arr_span)); // 8
std::cout << std::format("sizeof other_span: {}\n", sizeof(other_span)); // 16
std::cout << std::format("sizeof vec_span: {}\n", sizeof(vec_span)); // 16
```

### Creating a std::span
It is possible to create std::span from iterators & size, or from two iterators:
```cpp
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
```

### subspan, first, last
std::span contains few useful methods: subspan, first & last
```cpp
int arr[] = {1, 2, 3, 4, 5, 6};
std::span sp(arr, 6);

// subspan(start, count):
std::span sub = sp.subspan(2, /*count*/2);

// fist(count):
std::span subFirst3 = sp.first(3);

// last(count):
std::span subLast4 = sp.last(4);
```
### return values
std::span can be usefule when we want to return non-owning reference & handle gracefully empty not-existing values
```cpp
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

// . . . 
ConfigManager manager;
auto dbConfig = manager.getConfig("database");
for (auto byte : dbConfig)
    std::cout << static_cast<char>(byte);

auto errCfg = manager.getConfig("error"); // not present
for (auto byte : errCfg)
    std::cout << static_cast<char>(byte);
```
# std::start_lifetime_as
To convert bytes to different structure without undefined behaviour, in C++23 was added function std::start_lifetime_as.
The problem is no major compiler supports it (02.2026). It is possible to implement it (code by Robert Leahy, cppcon 2022)
```cpp
template <typename T>
[[nodiscard]] T* start_lifetime_as(void* mem) noexcept {
    auto bytes = new (mem) unsigned char[sizeof(T)];
    auto ptr   = reinterpret_cast<T*>(bytes);
    (void)*ptr;
    return ptr;
}
template <typename T>
[[nodiscard]] const T* start_lifetime_as(const void* mem) noexcept {
    const auto mp    = const_cast<void*>(mem);
    const auto bytes = new (mp) unsigned char[sizeof(T)];
    const auto ptr   = reinterpret_cast<const T*>(bytes);
    (void)*ptr;
    return ptr;
}
```