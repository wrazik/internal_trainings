/* C run-time library (or CRT)  provides atol (ascii to long), atof(acii to float), atoi (ascii to integer)
long atol(const char *str);
float atof(const char *str);
int atoi(const char *str);
*/

#include <print>

int main() {
    long correctLong = atol("4817987419  ");
    int correctInt =  atoi("  2137");
    float correctFloat = atof("88.33");

    std::println("correctLong: {}, correctInt: {}, correctFloat: {}", correctLong, correctInt, correctFloat);

    long incorrectLongWithString = atol("48dupa43");
    int incorrectIntOverflow = atoi("4817987419");
    int incorrectIntNoValidNumber = atoi("Twoja stara");
    float incorrectFloat = atof("21,37");

    std::println("48dupa43 parsed as {}", incorrectLongWithString);
    std::println("4817987419 parsed as {}", incorrectIntOverflow);
    std::println("Twoja stara parsed as {}", incorrectIntNoValidNumber);
    std::println("21,37 parsed as {}", incorrectFloat);

    /* Summary: unusable, cannot verify if works correctly */
}