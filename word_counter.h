#pragma once

#include "entry.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

class word_counter
{
    std::vector<entry> entryList;
    void sortListByValue();
    std::vector<entry>::iterator &getEntryNonConst(std::string word);

public:
    word_counter() = default;
    word_counter(std::vector<entry> &entryList) : entryList(entryList){};

    // look up values
    std::vector<entry>::const_iterator const &getEntry(std::string const &word);
    bool isEmpty() const;
    bool hasWord(std::string const &word) const;
    entry const &highesCount() const;
    entry const &lowestCount() const;
    int numberOfWords() const;
    std::vector<entry> const &getList() const;

    // modifires
    void addWord(std::string &word);
    void addEntry(entry &ent);
    void addWords(std::istream &stream);
    void addWords(std::vector<std::string> arr);
    void addWords(std::vector<entry> arr);

    void clearCounter();

    // operators
    word_counter &operator+=(word_counter const &wc);
    entry const &operator[](std::string const &word) const;
    entry &operator[](std::string const &word);

    // iterators
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