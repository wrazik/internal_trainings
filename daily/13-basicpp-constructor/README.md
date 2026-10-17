# Special operations & constructors
In C++ we have **6 special member operations**:
1. Default constructor
2. Destructor
3. Copy constructor
4. Move constructor
5. Copy assignment operator
6. Move assignment operator

### Rule of 0
Prefer **not defining special operations** when the class only contains RAII members.

Example:
```cpp
struct Named_map {
public:
    explicit Named_map(const std::string& n) : name(n) {}
    
private:
    std::string name;
    std::map<int, int> rep;
};
```

All copy/move/destruction logic is handled automatically by members.

### Rule of 5
If you **define or delete any of the special operations**, you should define or delete **all five**:
- destructor
- copy constructor
- move constructor
- copy assignment
- move assignment

Example:

```cpp
struct RAII_Example {
    RAII_Example() : ptr(new int()) { }
    ~RAII_Example() { delete ptr; }

    int *ptr{nullptr};

    RAII_Example(const RAII_Example &) = delete;
    RAII_Example(RAII_Example &&) = delete;
    RAII_Example& operator=(const RAII_Example &) = delete;
    RAII_Example& operator=(RAII_Example &&) = delete;
};
```

Uninitialized members may contain **garbage values**:

```cpp
Foo uninitialized;
```

Brace initialization guarantees zero-initialization:
```cpp
Foo brace_init {};
```

Different initialization styles:
```cpp
Foo f2{Foo()};
Foo f3{Foo{}};
Foo f4{34};
Foo f5 = {34};
```

Brace initialization prevents **narrowing conversions**:
```cpp
Bar b(21.37);   // allowed
Bar b2 = 21.37; // allowed
Bar b3{21.37};  // error: narrowing
```

If a class has **no constructors**, the compiler generates a default one.

Example:

```cpp
struct NoConstructor {
    int x;
};
```

Special operations can be explicitly controlled:
- `= default` - use compiler-generated implementation
- `= delete` - forbid usage

Some members prevent implicit constructors:
- reference members
- const members without initialization

Example:

```cpp
struct ReferenceMember {
    int &x;
};
struct ConstMember {
    const int x;
};
```

Declaring different constructors or having private destructor also prevents from generating default constructor.

A constructor can call another constructor of the same class (or base class).
```cpp
struct DelegatingConstructor {
    DelegatingConstructor(int x, int y): x{x}, y{y} { }
    DelegatingConstructor(int x): DelegatingConstructor(x, 0) {}
    DelegatingConstructor(): DelegatingConstructor(0, 0) {}

    int x;
    int y;
};
```

Constructors with a single parameter allow implicit conversions.

Example:
```cpp
Product(int x): x{x} {}

Product numbers = 100.2; // OK
```

The compiler implicitly constructs a `Product`.

To prevent this, use `explicit`:
```cpp
explicit Product(int v);
```