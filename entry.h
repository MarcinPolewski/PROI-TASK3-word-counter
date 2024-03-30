#pragma once
#include <string>

class entry
{
    int count;
    std::string value;

public:
    entry() = default;
    entry(std::string value, int coun = 1) : value(value), count(count){};

    entry operator++(int);                // post increment (for instance entry++)
    std::string const &operator*() const; // retreave value
    operator int();                       // retreave count
};

std::ostream &operator<<(std::ostream &stream, entry const &ent);
std::ostream &operator>>(std::ostream &stream, entry const &ent);