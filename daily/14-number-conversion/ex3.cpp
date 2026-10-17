/* C++11
C++11 brought stoul() [and its variations stoi(), stol(), stoll(), stoull(), stof(), stod(), stold()] and is defined as:

unsigned long stoul(const std::string& str, size_t* idx = 0, int base = 10);
*/

#include <print>

int main() {
    {
        int correctInt = std::stoi("324");
        float correctFloat = std::stof("21.37");
        std::println("correct int: {}", correctInt);
        std::println("correct float: {}", correctFloat);
    }
    {
        try{
            float num = std::stof("twoja_stara");
            std::println("num: {}", num);
        }
        catch(const std::exception& e){
            std::println("Invalid input: {}",  e.what());
        }
    }
    {
        size_t idx = 0;
        float num = std::stof("21,37", &idx);
        std::println("num: {}, idx: {}", num, idx);
    }
}
