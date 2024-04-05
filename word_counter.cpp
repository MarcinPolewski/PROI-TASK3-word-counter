#include "word_counter.h"

std::vector<entry>::iterator word_counter::getEntryNonConst(std::string word)
{
    entry temp(word, 1);
    std::vector<entry>::iterator it = std::lower_bound(entryList.begin(), entryList.end(), temp);
    if (it == entryList.end() || *temp != *(*it))
        return entryList.end();
    return it;
}

std::vector<entry>::const_iterator word_counter::getEntry(std::string const &word) const
{
    entry temp(word, 1);
    std::vector<entry>::const_iterator it = std::lower_bound(entryList.begin(), entryList.end(), temp);
    if (it == entryList.end() || *temp != *(*it))
        return entryList.end();
    return it;
}

bool word_counter::isEmpty() const
{
    return entryList.size() == 0;
}

bool word_counter::hasWord(std::string const &word) const
{
    return getEntry(word) != entryList.end();
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

    std::vector<entry> entList;

    stream.get(); // skipping the first element

    std::istringstream ss("");

    entry e;
    while (stream >> ss && ss.getStr() != "}")
    {
        ss >> e;
        entList.push_back(e);
    }
}