#pragma once

#include "entry.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class word_counter
{
    std::vector<entry> entryList;
    void sortListByValue();

public:
    word_counter() = default;
    word_counter(std::vector<entry> const &entryList) : entryList(entryList) { sortListByValue(); };

    // look up values
    std::vector<entry>::const_iterator getEntry(std::string const &word) const;
    std::vector<entry>::iterator getEntry(const std::string &word);
    bool isEmpty() const;
    bool hasWord(std::string const &word) const;
    int size() const;
    std::vector<entry> const &getList() const;

    // modifires
    void addWord(std::string const &word);
    void addEntry(entry const &ent);
    void addWords(std::istream &stream);
    void addWords(std::vector<std::string> const &arr);
    void addWords(std::vector<entry> const &arr);

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
        alpha_iterator(std::vector<entry>::const_iterator iter) : it(iter){};
        alpha_iterator operator++(int);
        alpha_iterator &operator++();
        entry const &operator*() const;
        bool operator!=(alpha_iterator const &wc) const;
    };
    class freq_iterator
    {
        std::vector<entry>::const_iterator it;
        std::vector<entry>::const_iterator entryListBegin;
        std::vector<entry>::const_iterator entryListEnd;

        std::vector<entry>::const_iterator findNext();

    public:
        freq_iterator(std::vector<entry>::const_iterator entryListBegin,
                      std::vector<entry>::const_iterator entryListEnd);
        freq_iterator(std::vector<entry>::const_iterator iter,
                      std::vector<entry>::const_iterator entryListBegin,
                      std::vector<entry>::const_iterator entryListEnd)
            : it(iter), entryListBegin(entryListBegin), entryListEnd(entryListEnd){};
        freq_iterator operator++(int);
        freq_iterator &operator++();
        entry const &operator*() const;
        bool operator!=(freq_iterator const &wc) const;
    };

    alpha_iterator alphaBegin();
    alpha_iterator alphaEnd();

    freq_iterator freqBegin();
    freq_iterator freqEnd();
};

std::ostream &operator<<(std::ostream &stream, const word_counter &counter); // loads counter to stream
std::istream &operator>>(std::istream &stream, word_counter &counter);       // read counter status from strream