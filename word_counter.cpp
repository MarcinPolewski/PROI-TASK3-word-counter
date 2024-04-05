#include "word_counter.h"

std::vector<entry>::const_iterator &word_counter::getEntryNonConst(std::string word)
{
    entry temp = entry(word, 1);
    return std::lower_bound(entryList.begin(), entryList.end(), temporary);
}

std::vector<entry>::iterator entry &word_counter::getEntry(std::string const &word)
{
    entry temp = entry(word, 1);
    return std::lower_bound(entryList.begin(), entryList.end(), temporary);
}

bool word_counter::isEmpty() const
{
    return entryList.size() == 0;
}

bool word_counter::hasWord(std::string const &word) const
{
    entry temporary(word, 1);
    return std::binary_search(entryList.begin(), entryList.end(), temporary);
}
entry const &word_counter::highesCount() const
{
    if (isEmpty())
        throw std::runtime_error("cannot find max element on empty list");

    int maxElementIdx = 0;
    for (auto it = entryList.begin() + 1; it != entryList.end(); it++)
    {
        if (*it > entryList[maxElementIdx])
            maxElementIdx = it - entryList.begin();
    }
    return entryList[maxElementIdx];

    // entry const &max = entryList[0];
    // for (auto const &it : entryList)
    // {
    //     if (max < it)
    //         max = it;
    // }
    // return max;
}

entry const &word_counter::lowestCount() const
{
    if (isEmpty())
        throw std::runtime_error("cannot find max element on empty list");

    int minElementIdx = 0;
    for (auto it = entryList.begin() + 1; it != entryList.end(); it++)
    {
        if (*it < entryList[minElementIdx])
            minElementIdx = it - entryList.begin();
    }
    return entryList[minElementIdx];
    // if (isEmpty())
    //     throw std::runtime_error("cannot find min element on empty list");

    // entry min = entryList[0];
    // for (auto const &it : entryList)
    // {
    //     if (min > it)
    //         min = it;
    // }
    // return min;
}

int word_counter::numberOfWords() const
{
    int wordCount = 0;
    for (auto const &it : entryList)
    {
        wordCount += (int)it;
    }

    return wordCount;
}
const std::vector<entry> &word_counter::getList() const
{
    return entryList;
}

// modifires
void word_counter::addWord(std::string &word)
{
    entry &ent = getEntryNonConstReference(word);
    if (ent == entryList.end())
        addWord(word);
    else
        ent++;
}

void word_counter::addEntry(entry &ent)
{
    int idx = getIdx(*ent);
    if (idx == -1)
        entryList.push_back(ent);
    else
        entryList[idx] += ent;
}

void word_counter::addWords(std::istream &stream)
{
    std::string s;
    while (stream >> s)
        addWord(s);
}
void word_counter::addWords(std::vector<std::string> arr)
{
    for (auto it : arr)
        addWord(it);
}
void word_counter::addWords(std::vector<entry> arr)
{
    for (auto it : arr)
    {
        addEntry(it);
    }
}

void word_counter::clearCounter()
{
    entryList.clear();
}

word_counter &word_counter::operator+=(word_counter const &wc)
{
    for (auto it : wc.getList())
        addEntry(it);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const word_counter &counter) // loads counter to stream
{
    stream << "{\n";
    for (auto const &it : counter.getList())
    {
        stream << "  " << it << '\n';
    }
    stream << "}\n";
    return stream;
}
std::istream &operator>>(std::istream &stream, word_counter &counter) // read counter status from strream
{

    // std::vector<entry> entList;

    // stream.get(); // skipping the first element

    // std::istringstream ss("");

    // entry e;
    // while (stream >> ss && ss.getStr() != "}")
    // {
    //     ss >> e;
    //     entList.push_back(e);
    // }

    return stream;
}