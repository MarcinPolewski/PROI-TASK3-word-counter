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
    //     return 2;
    // }

    // 2. read moby dick
    try
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        std::ifstream fileReader = openFileForReading("moby_dick.txt");
        counter.addWords(fileReader);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        std::cout << "read moby_dick.txt in: " << time / std::chrono::milliseconds(1) << " ms.\n";
        fileReader.close();
    }
    catch (...)
    {
        std::cout << "opening moby_dick.txt for reading unsuccesssful\n";
        return 2;
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
        return 2;
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

    // 5. iterate over word counter by frequency
    auto start_time = std::chrono::high_resolution_clock::now();
    for (auto it = counter.freqBegin(); it != counter.freqEnd(); it++)
    {
        *it;
        // std::cout << *it << '\n';
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    std::cout << "iterated over moby dick by frequency in: " << time / std::chrono::milliseconds(1) << " ms.\n";

    // 5.Iterating alphabetically
    start_time = std::chrono::high_resolution_clock::now();
    for (auto it = counter.alphaBegin(); it != counter.alphaEnd(); it++)
    {
        *it;
        // std::cout << *it << '\n';
    }
    end_time = std::chrono::high_resolution_clock::now();
    time = end_time - start_time;
    std::cout << "iterated over moby dick alphabetically in: " << time / std::chrono::milliseconds(1) << " ms.\n";

    return 0;
}