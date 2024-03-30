#pragma once

#include "entry.h"
#include "vector"

#include <iostream>

class word_counter
{
    std::vector<entry> entryList;
    void sortEntryList();

public:
    word_counter() = default;
    word_counter(std::vector<entry> &entryList) : entryList(entryList) { sortEntryList(); };

    // look up values
    int find(std::string &word) const; // returns index in list of element or -1 if it was not found
    bool isEmpty() const;
    bool hasWord(std::string &word) const;
    entry highesCount() const;
    entry lowestCount() const;
    int numberOfWords() const;

    // modifires
    void addWord(std::string &word);
    void addWords(std::ostream &stream);
    void addWords(std::vector<std::string> arr);
    void clearCounter();

    word_counter &operator+=(word_counter const &wc);

    class alpha_iterator
    {
    };
    class freq_iterator
    {
    };
};

std::ostream &operator<<(std::ostream &stream, const word_counter &counter); // loads counter to stream
std::istream &operator>>(std::istream &stream, word_counter &counter);       // read counter status from strream