#include "entry.h"

entry::entry(std::string &value, int count)
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

bool entry::operator<(const entry &ent) const
{
    return count < (int)ent;
}

bool entry::operator>(const entry &ent) const
{
    return count > (int)ent;
}

bool entry::cmp_lexicographically(const entry &lEntry, const entry &rEntry) const
{
    return *lEntry > *rEntry;
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
    s += ",";
    s += std::to_string(count);
    s += "]";
    return s;
}

std::ostream &operator<<(std::ostream &stream, entry const &ent)
{
    stream << ent.getString();
    return stream;
}

int findLastComma(std::string s)
{
    for (int i = s.size() - 1; i > 0; i--)
    {
        if (s[i] == ',')
            return i;
    }
    return -1;
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
    std::string s;
    stream >> s;

    int lastCommaIdx = findLastComma(s);

    if (s.front() != '[' ||
        s.back() != ']' ||
        lastCommaIdx == -1 ||
        lastCommaIdx == 1 ||          // there's no first value
        lastCommaIdx == s.size() - 2) // there's no second value
        throw std::runtime_error("invalid entry syntax");

    try
    {
        std::string value = s.substr(1, lastCommaIdx - 1);
        int count = std::stoi(s.substr(lastCommaIdx + 1, s.size() - lastCommaIdx - 1));
        ent = entry(value, count);
    }
    catch (...)
    {
        throw std::runtime_error("could not extract individual values");
    }

    return stream;
}
