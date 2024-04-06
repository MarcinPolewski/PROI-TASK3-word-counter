#include "word_counter.h"

#include <fstream>
#include <stdexcept>

std::ifstream openFileForReading(std::string filePath)
{
    std::ifstream fileReader(filePath);
    if (!fileReader.good())
    {
        throw std::runtime_error("could not open file");
    }
    return fileReader;
}

std::ofstream openFileForWriting(std::string filePath)
{
    std::ofstream fileReader(filePath);
    if (!fileReader.good())
    {
        throw std::runtime_error("could not open file");
    }
    return fileReader;
}

int main()
{
    word_counter counter;
    // std::ifstream fileReader;
    std::ofstream fileWriter;
    // 1. load word_counter status from file
    // try
    // {
    //     std::ifstream fileReader = openFileForReading("wordCounterState.txt");
    //     fileReader >> counter;
    //     fileReader.close();
    // }
    // catch (...)
    // {
    //     std::cout << "opening wordCounterState.txt for reading unsuccesssful\n";
    // }

    // 2. read moby dick
    try
    {
        std::ifstream fileReader = openFileForReading("moby_dick.txt");
        counter.addWords(fileReader);
        fileReader.close();
    }
    catch (...)
    {
        std::cout << "opening moby_dick.txt for reading unsuccesssful\n";
    }

    // 3. write  word_counter to file(erasing previous contents)
    try
    {
        fileWriter = openFileForWriting("wordCounterState.txt");
        fileWriter << counter;
        fileWriter.close();
    }
    catch (...)
    {
        std::cout << "opening wordCounterState.txt for writing unsuccessful\n";
    }

    // 4. display statistics on cout
    std::cout << "top 10 least popular words:\n";
    int cnt = 0;
    for (auto it = counter.freqBegin(); it != counter.freqEnd() && cnt <= 10; it++, cnt++)
    {
        std::cout << *it << '\n';
    }

    std::cout << "\nmost popular word:\n";
    std::cout << counter.highesCount() << '\n';

    std::cout << "\ntotal sum of words:\n";
    std::cout << counter.numberOfWords() << '\n';

    std::cout << "\ndoes stream have words:\n";
    std::cout << "banana: " << (counter.hasWord("banana") ? "yes" : "no") << '\n';
    std::cout << "circumambulate: " << (counter.hasWord("circumambulate") ? "yes" : "no") << '\n';

    return 0;
}