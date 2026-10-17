/* C++ kicks in
 * istringstream
*/

#include <sstream>
#include <print>

int main() {
    {
        std::istringstream intstream("2137");
        int value;
        intstream >> value;
        std::println("value: {}", value);
    }
    {
        std::istringstream floatstream("21.37");
        float value;
        floatstream >> value;
        std::println("value: {}", value);
    }
    {
        std::istringstream floatstream("21,37");
        float value;
        floatstream >> value;
        if (floatstream.fail()) {
            std::println("floatstream fail");
        }
        std::println("value: {}", value);
    }
    {
        std::istringstream incorrectstream("dupa");
        float value;
        incorrectstream >> value;
        std::println("value: {}", value);
        if (incorrectstream.fail()) {
            std::println("floatstream fail");
        }
    }
}
