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
    stream << "{\n";
    for (auto const &it : counter.getList())
    {
        stream << it << '\n';
    }
    stream << "}\n";
    return stream;
}
std::istream &operator>>(std::istream &stream, word_counter &counter) // read counter status from strream
{

    std::vector<entry> entList;

    char c;
    stream >> c;
    if (!stream.good() || c != '{')
        throw std::invalid_argument("unable to read word_counter from stream");

    entry temopraryEntry;
    while (stream.good())
    {
        try
        {
            stream >> temopraryEntry;
            entList.push_back(temopraryEntry);
        }
        catch (std::invalid_argument)
        {
            break;
        }
    }

    counter.addWords(entList);

    return stream;
}
// implementation of alpha_iterator
word_counter::alpha_iterator word_counter::alpha_iterator::operator++(int)
{
    word_counter::alpha_iterator oldValue = *this;
    ++it;
    return oldValue;
}
word_counter::alpha_iterator &word_counter::alpha_iterator::operator++()
{
    ++it;
    return *this;
}
entry const &word_counter::alpha_iterator::operator*() const
{
    return *it;
}
bool word_counter::alpha_iterator::operator!=(alpha_iterator const &wc) const
{
    return it != wc.it;
}

word_counter::alpha_iterator word_counter::alphaBegin()
{
    return alpha_iterator(entryList.begin());
}
word_counter::alpha_iterator word_counter::alphaEnd()
{
    return alpha_iterator(entryList.end());
}

// implementation of freq_iterator

word_counter::freq_iterator::freq_iterator(std::vector<entry>::const_iterator entryListBegin, std::vector<entry>::const_iterator entryListEnd)
    : entryListBegin(entryListBegin), entryListEnd(entryListEnd)
{
    std::vector<entry>::const_iterator firstElement = entryListBegin;
    for (std::vector<entry>::const_iterator i = entryListBegin + 1; i != entryListEnd; i++)
    {
        if ((int)(*i) < (int)(*firstElement))
            firstElement = i;
    }

    it = firstElement;
}

std::vector<entry>::const_iterator word_counter::freq_iterator::findNext()
{
    /*
        we are looking for the smallest greater element, that is same count but greater
        alphabetically or bigger in count.

        elements greater alphabetically are only to the right of it, elements of smaller
        count could be everywhere
    */
    std::vector<entry>::const_iterator nextMinimal = it;
    bool nextFound = false;
    for (std::vector<entry>::const_iterator i = it + 1; i != entryListEnd; i++)
    {
        if ((int)(*i) == (int)(*it)) // if count is the same, but alphabethically is greater(must be, because list is sorted)
            return i;
        // if it.count < i.count and(!nextFound or (nextFound && (int)(*i) < (int)(*nextMinimal)))
        if ((int)(*it) < (int)(*i) && (!nextFound || (int)(*i) < (int)(*nextMinimal)))
        {
            nextMinimal = i;
            nextFound = true;
        }
    }
    for (std::vector<entry>::const_iterator i = entryListBegin; i != it; i++)
    {
        if ((int)(*it) < (int)(*i) && (!nextFound || (int)(*i) < (int)(*nextMinimal)))
        {
            nextMinimal = i;
            nextFound = true;
        }
    }

    if (!nextFound)
        return entryListEnd;
    return nextMinimal;
}

word_counter::freq_iterator word_counter::freq_iterator::operator++(int)
{
    auto oldValue = *this;
    it = findNext();
    return oldValue;
}
word_counter::freq_iterator &word_counter::freq_iterator::operator++()
{
    it = findNext();
    return *this;
}
entry const &word_counter::freq_iterator::operator*() const
{
    return *it;
}
bool word_counter::freq_iterator::operator!=(freq_iterator const &wc) const
{
    return it != wc.it;
}

word_counter::freq_iterator word_counter::freqBegin()
{
    return freq_iterator(entryList.begin(), entryList.end());
}
word_counter::freq_iterator word_counter::freqEnd()
{
    return freq_iterator(entryList.end(), entryList.begin(), entryList.end());
}