#include "entry.h"

entry::entry(std::string const &value, int count)
{
    if (count < 1)
        throw std::invalid_argument("count cannot be of negative value");
    this->count = count;
    this->value = value;
}

entry entry::operator++(int)
{
    count++;
    return *this;
}

bool entry::operator==(const entry &ent) const
{
    return (value == *ent && count == (int)ent);
}

bool entry::operator==(const std::string &st) const
{
    return value == st;
}

bool entry::operator<(const entry &ent) const
{
    return value < *ent;
}

bool entry::operator>(const entry &ent) const
{
    return value > *ent;
}

std::string const &entry::operator*() const
{
    return value;
}

entry::operator int() const
{
    return count;
}

std::string entry::getString() const
{
    std::string s = "[";
    s += value;
    s += ' ';
    s += std::to_string(count);
    s += ']';
    return s;
}

std::ostream &operator<<(std::ostream &stream, entry const &ent)
{
    stream << ent.getString();
    return stream;
}

entry &entry::operator+=(const entry &ent)
{
    if (value != *ent)
        throw std::invalid_argument("cannot add two entries of different words");
    count += (int)ent;
    return *this;
}

std::istream &operator>>(std::istream &stream, entry &ent)
{
    std::string word;
    int count;
    char left, right;

    stream >> left;
    if (stream.eof()) // checking if provided stream is empty alredy
        return stream;
    stream >> word >> count >> right;
    // if non int value is provided inplace of count
    // stream would put fail bit on, next values would not be read
    if (stream.fail() || left != '[' || right != ']')
        throw std::invalid_argument("invalid syntax of entry, expected: [word count]");

    ent = entry(word, count);

    return stream;
}
