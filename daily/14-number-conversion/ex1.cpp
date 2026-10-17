/* ANSI C89 introduced: strtoul() and its associates strtof(), strtod(), strtold(), strtol(), strtoll() and strtoull()]

unsigned long strtoul(const char *nptr, char **endptr, int base);
double strtod(const char *nptr, char **endptr, int base);
...
*/

#include <print>
#include <cstdlib>

int main() {
    long correctLong = strtol("4817987419  ", nullptr, 10);
    unsigned long correctUnsignedLong = strtol("48179874192344  ", nullptr, 10);
    float correctFloat = strtof("88.33", nullptr);

    std::println("correctLong: {}", correctLong);
    std::println("correctUnsignedLong: {}", correctUnsignedLong);
    std::println("correctUnsignedLong: {}", correctFloat);

    // Parsing long chars
    {
        const char* str = "4243 54455 2223 323 523 du3pa";
        std::println("str: {}", str);
        char* end = nullptr;
        for (long parsed = strtol(str, &end, 10); str != end;)
        {
            str = end;
            std::println("parsed: {}", parsed);
            parsed = strtol(str, &end, 10);
        }
    }

    // Parsing error
    {
        const char* incorrect_str = "dupa";
        char* end = nullptr;
        long incorrect_val = strtol(incorrect_str, &end, 10);
        if (end == incorrect_str) {
            std::println("Incorrect conversion");
        }
        else {
            std::println("correct: {}", incorrect_val);
        }
    }
}
