#include "user.h"
#include <iostream>

User::User() {
    std::cout << "User::User() " << name << '\n';
}

User::User(std::string str) : name(std::move(str)) {
    std::cout << "User::User(std::string str) " << name << '\n';
}

User::~User() {
    std::cout << "User::~User " << name << '\n';
}

User::User(const User& other) : name(other.name) {
    std::cout << "User::User(const User&) " << name << '\n';
}

User::User(User&& other) noexcept : name(std::move(other.name)) {
    std::cout << "User::User(User&&) " << name << '\n';
}

User& User::operator=(const User& other) {
    if (this != &other)
        name = other.name;
    std::cout << "User::operator=(const User&) " << name << '\n';
    return *this;
}

User& User::operator=(User&& other) noexcept {
    if (this != &other)
        name = std::move(other.name);
    std::cout << "User::operator=(User&&) " << name << '\n';
    return *this;
}

bool operator<(const User& u1, const User& u2) {
    return u1.name < u2.name;
}
