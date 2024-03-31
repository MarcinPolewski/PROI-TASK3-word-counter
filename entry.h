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
    entry(std::string &value, int count = 1);

    entry operator++(int);                // post increment (for instance entry++)
    std::string const &operator*() const; // retreave value
    operator int() const;                 // retreave count
    entry &operator+=(const entry &ent);
    bool operator==(const entry &ent) const;
    bool operator>(const entry &ent) const; // compares count
    bool operator<(const entry &ent) const;

    // true if lEntry.value is greater
    bool cmp_lexicographically(const entry &lEntry, const entry &rEntry) const;

    std::string getString() const;
};

int findLastComma(std::string s);

std::ostream &operator<<(std::ostream &stream, entry const &ent);
std::istream &operator>>(std::istream &stream, entry &ent);