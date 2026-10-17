#include <charconv>
#include <iostream>
#include <map>
#include <cstring>
#include <memory>

#include "user.h"

void example1() {
    std::map<std::string, User> mapNicks;
    mapNicks["Johnny"] = User("John Doe");
    std::cout << "after[]...\n";

    std::map<int, std::unique_ptr<int>> m;
    if (m[5]) {
        std::cout << "Exist!\n";
    }
}

void example2() {
    std::map<std::string, User> mapNicks;
    mapNicks.insert({"Johnny", User("John Doe")});
    std::cout << "after[]...\n";
}

void example3() {
    std::map<std::string, User> mapNicks;
    mapNicks.emplace("Johnny", User("John Doe"));
    std::cout << "after[]...\n";
}

void example4() {
    std::map<std::string, User> mapNicks;
    mapNicks.emplace("Johnny", "John Doe");
    std::cout << "after[]...\n";
}

void example5() {
    std::map<std::string, std::string> m;
    m["Hello"] = "World";
    std::string s = "C++";
    m.emplace("Hello", std::move(s));
    std::cout << "string s = " << s << '\n';
    std::cout << "m[\"Hello\"] = " << m["Hello"] << '\n';
}

void example6() {
    std::map<std::string, std::string> m;
    m["Hello"] = "World";
    std::string s = "C++";
    m.try_emplace("Hello", std::move(s));
    std::cout << "string s = " << s << '\n';
    std::cout << "m[\"Hello\"] = " << m["Hello"] << '\n';
}

void example7() {
    std::map<std::string, User> mapNicks;
    auto [it, inserted] = mapNicks.insert_or_assign("Johnny", User("John Doe"));
    std::cout << "after insert_or_assign...\n";
    std::cout << "inserted: " << inserted << '\n';
    auto [it2, inserted2] = mapNicks.insert_or_assign("Johnny", User("Another John"));
    std::cout << "after insert_or_assign 2...\n";
    std::cout << "inserted: " << inserted2 << '\n';
    std::cout << "-> " << mapNicks["Johnny"].name << '\n';
}

void example8() {
    std::map<std::string, User> mapShortcuts {
        { "Johnny", User {"John D."}},
        { "X", User {"Mark X."}},
        { "M", User {"Marry Jones"}},
    };

    if (mapShortcuts.contains("X")) {
        std::cout << "X is present\n";
    }
}

void example9() {
    std::map<std::string, User> mapShortcuts {
        { "Johnny", User {"John D."}},
        { "X", User {"Mark X."}},
        { "M", User {"Marry Jones"}},
    };

    auto print = [](const std::string& str, const std::map<std::string, User>& container) {
        std::cout << str;
        for (const auto& [key, val] : container)
            std::cout << key << " : " << val.name << '\n';
    };

    print("before\n", mapShortcuts);

    std::cout << "erasing...\n";

    std::erase_if(mapShortcuts, [](auto& elem) {
        return elem.first == "X";
    });

    print("after erase...\n", mapShortcuts);
}

void run(int example) {
    switch (example) {
        case 1:
            example1();
            break;
        case 2:
            example2();
            break;
        case 3:
            example3();
            break;
        case 4:
            example4();
            break;
        case 5:
            example5();
            break;
        case 6:
            example6();
            break;
        case 7:
            example7();
            break;
        case 8:
            example8();
            break;
        case 9:
            example9();
            break;
        default:
            ;
    }
}


int main(int argc, char** argv) {
    if (argc < 2) {
        return -1;
    }
    int res;
    const char* begin = argv[1];
    const char* end = argv[1] + std::strlen(argv[1]);
    std::from_chars(begin, end, res);
    run(res);
}