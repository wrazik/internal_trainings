#pragma once
#include <string>

struct User {
    std::string name {"default"};

    User();
    explicit User(std::string str);

    ~User();
    User(const User& other);

    User(User&& other) noexcept;

    User& operator=(const User& other);

    User& operator=(User&& other) noexcept;

    friend bool operator<(const User& u1, const User& u2);
};