#pragma once

#include "entry.h"
#include "vector"

#include <iostream>
#include <sstream>

class word_counter
{
    std::vector<entry> entryList;
    void sortListlexicographically();
    void sortListByFrequency();

public:
    word_counter() = default;
    word_counter(std::vector<entry> &entryList) : entryList(entryList){};

    // look up values
    int getIdx(std::string const &word) const; // returns index in list of element or -1 if it was not found
    const entry &getEntryReference(std::string const &word);
    bool isEmpty() const;
    bool hasWord(std::string const &word) const;
    entry highesCount() const;
    entry lowestCount() const;
    int numberOfWords() const;
    const std::vector<entry> &getList() const;

    // modifires
    void addWord(std::string &word);
    void addEntry(entry &ent);
    void addWords(std::istream &stream);
    void addWords(std::vector<std::string> arr);
    void addWords(std::vector<entry> arr);

    void clearCounter();

    word_counter &operator+=(word_counter const &wc);

    class alpha_iterator
    {
        std::vector<entry>::const_iterator it;

    public:
        alpha_iterator operator++(int);
        alpha_iterator &operator++();
        entry const &operator*() const;
        bool operator!=(alpha_iterator const &wc) const;
    };
    class freq_iterator
    {
        std::vector<entry>::const_iterator it;

    public:
        freq_iterator operator++(int);
        freq_iterator &operator++();
        entry const &operator*() const;
        bool operator!=(freq_iterator const &wc) const;
    };
};

std::ostream &operator<<(std::ostream &stream, const word_counter &counter); // loads counter to stream
std::istream &operator>>(std::istream &stream, word_counter &counter);       // read counter status from strream