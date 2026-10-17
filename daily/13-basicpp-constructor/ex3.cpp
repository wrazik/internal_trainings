#include <print>

// https://cppinsights.io/
struct NoConstructor {
    //implicit:
    // inline NoConstructor() noexcept { }
    int x;
};

struct AnotherConstructor {
    AnotherConstructor(int a): x{a} { }

    int x;
};

// AnotherConstructor x; // error
// AnotherConstructor x {}; // using custom ctor

struct Default {
    Default() = default;
    Default(int a): x{a} { }

    int x;
};

struct Deleted {
    Deleted() = delete;

    int x;
};

struct ReferenceMember {
    int &x;
};

//ReferenceMember rm;

struct ConstMember {
    const int x;
};

//ConstMember cm;

struct DeclaredCopyConstructor {
    DeclaredCopyConstructor(const DeclaredCopyConstructor&) = default;
//    DeclaredCopyConstructor(const UserDeclaredCopyConstructor&) = delete;
//    DeclaredCopyConstructor(const UserDeclaredCopyConstructor&) {};
};

//DeclaredCopyConstructor dcc;

struct MoveConstructor{
    MoveConstructor(MoveConstructor&&) = default;
//    MoveConstructor(MoveConstructor&&) = delete;
//    MoveConstructor(MoveConstructor&&) {};
};
//MoveConstructor mc;

struct CopyAssignment {
    CopyAssignment& operator=(CopyAssignment& ) = default;
};
CopyAssignment ca;

struct MoveAssignment {
    MoveAssignment& operator=(MoveAssignment&& ) = default;
};

MoveAssignment ma;

struct PrivateDestructor {
private:
    ~PrivateDestructor() = default;
};
//PrivateDestructor u;


int main() {
}
