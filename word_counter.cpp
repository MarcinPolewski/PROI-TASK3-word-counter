#include "word_counter.h"

int word_counter::getIdx(std::string const &word) const
{
    for (std::vector<entry>::const_iterator it = entryList.begin();
         it != entryList.end();
         it++)
    {
        if (**it == word)
            return it - entryList.begin();
    }
    return -1;
}

const entry &word_counter::getEntryReference(std::string const &word)
{
    int idx = getIdx(word);
    if (idx == -1)
        throw std::runtime_error("word not found");
    return entryList[idx];
}

bool word_counter::isEmpty() const
{
    return entryList.size() == 0;
}

bool word_counter::hasWord(std::string const &word) const
{
    return getIdx(word) != -1;
}
entry word_counter::highesCount() const
{
    if (isEmpty())
        throw std::runtime_error("cannot find max element on empty list");

    entry max = entryList[0];
    for (auto const &it : entryList)
    {
        if (max < it)
            max = it;
    }
    return max;
}

entry word_counter::lowestCount() const
{
    if (isEmpty())
        throw std::runtime_error("cannot find min element on empty list");

    entry min = entryList[0];
    for (auto const &it : entryList)
    {
        if (min > it)
            min = it;
    }
    return min;
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
    int idx = getIdx(word);
    if (idx == -1)
        entryList.push_back(entry(word, 1));
    else
        entryList[idx]++;
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