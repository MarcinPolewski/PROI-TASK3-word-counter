#pragma once

#include "entry.h"

#include <iostream>
#include <sstream>
#include <vector>

class word_counter
{
    std::vector<entry> entryList;
    void sortListByValue();
    std::vector<entry>::iterator getEntryNonConst(std::string word);

public:
    word_counter() = default;
    word_counter(std::vector<entry> &entryList) : entryList(entryList) { sortListByValue(); };

    // look up values
    std::vector<entry>::const_iterator getEntry(std::string const &word) const;
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