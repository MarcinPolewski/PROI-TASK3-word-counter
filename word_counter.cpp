#include "word_counter.h"

void word_counter::sortListByValue()
{
    std::sort(entryList.begin(), entryList.end());
}

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
entry const &word_counter::highesCount() const
{
    if (isEmpty())
        throw std::runtime_error("cannot find max element on empty list");

    int maxElementIdx = 0;
    for (auto it = entryList.begin() + 1; it != entryList.end(); it++)
    {
        // comparing counts
        if ((int)(*it) > (int)(entryList[maxElementIdx]))
            maxElementIdx = it - entryList.begin();
    }
    return entryList[maxElementIdx];
}

entry const &word_counter::lowestCount() const
{
    if (isEmpty())
        throw std::runtime_error("cannot find max element on empty list");

    int minElementIdx = 0;
    for (auto it = entryList.begin() + 1; it != entryList.end(); it++)
    {
        if ((int)(*it) < (int)(entryList[minElementIdx]))
            minElementIdx = it - entryList.begin();
    }
    return entryList[minElementIdx];
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
    entry temp(word, 1);
    std::vector<entry>::iterator it = std::lower_bound(entryList.begin(), entryList.end(), temp);

    if (it == entryList.end() || *temp != *(*it)) // no such word in list
        entryList.insert(it, entry(word, 1));
    else
        (*it)++;
}

void word_counter::addEntry(entry &ent)
{
    std::vector<entry>::iterator it = std::lower_bound(entryList.begin(), entryList.end(), ent);
    if (it == entryList.end() || *ent != *(*it)) // no such word in list
        entryList.insert(it, ent);
    else
        (*it) += ent;
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

entry const &word_counter::operator[](std::string const &word) const
{
    std::vector<entry>::const_iterator it = getEntry(word);
    if (it == entryList.end())
        throw std::invalid_argument("word counter does not have such word");
    return *it;
}
entry &word_counter::operator[](std::string const &word)
{
    std::vector<entry>::iterator it = getEntryNonConst(word);
    if (it == entryList.end())
        throw std::invalid_argument("word counter does not have such word");
    return *it;
}

std::ostream &operator<<(std::ostream &stream, const word_counter &counter) // loads counter to stream
{
    // stream << "{\n";
    // for (auto const &it : counter.getList())
    // {
    //     stream << "  " << it << '\n';
    // }
    // stream << "}\n";
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