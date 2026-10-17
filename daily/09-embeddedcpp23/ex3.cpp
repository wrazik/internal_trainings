int val = 2;
const int const_val = 3;
constexpr int constexpr_val = 4;
constinit int constinit_val = 5;

int main (int argc, char* argv[]) {
// constexpr_val = argc; // const, cannot me be modified
 constinit_val = argc; // OK
}