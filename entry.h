#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

class entry
{
    int count;
    std::string value;

public:
    entry() = default;
    entry(std::string const &value, int count = 1);

    entry operator++(int);                // post increment (for instance entry++)
    std::string const &operator*() const; // retreave value
    operator int() const;                 // retreave count
    entry &operator+=(const entry &ent);
    // bool operator==(const entry &ent) const;
    // bool operator==(const std::string &st) const; // dodać !!!!!!
    bool operator>(const entry &ent) const; // compares values
    bool operator<(const entry &ent) const;

    std::string getString() const;
};

std::ostream &operator<<(std::ostream &stream, entry const &ent);
std::istream &operator>>(std::istream &stream, entry &ent);