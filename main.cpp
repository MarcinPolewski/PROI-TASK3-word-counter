#include "word_counter.h"

#include <fstream>
#include <stdexcept>

int main()
{
    // 1. read state
    word_counter counter;
    std::ifstream wordCounterStateReader("wordCounterState.txt");
    if (!wordCounterStateReader.good())
    {
        std::cout << "wordCounterState.txt for reading unsuccesssful\n";
        return 2;
    }
    wordCounterStateReader >> counter;
    wordCounterStateReader.close();

    // 2. read moby dick

    auto start_time = std::chrono::high_resolution_clock::now();
    std::ifstream fileReader("moby_dick.txt");
    if (!fileReader.good())
    {
        std::cout << "opening moby_dick.txt for reading unsuccesssful\n";
        return 2;
    }
    counter.addWords(fileReader);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    std::cout << "read moby_dick.txt in: " << time / std::chrono::milliseconds(1) << " ms.\n";
    fileReader.close();

    // 3. write  word_counter to file(erasing previous contents)
    std::ofstream fileWriter("wordCounterState.txt");
    if (!fileWriter.good())
    {
        throw std::runtime_error("could not open file");
    }

    fileWriter << counter;
    fileWriter.close();

    // 4. display statistics on cout
    std::cout << "top 10 least popular words:\n";
    int cnt = 0;
    for (auto it = counter.freqBegin(); it != counter.freqEnd() && cnt <= 10; it++, cnt++)
    {
        std::cout << *it << '\n';
    }

    std::cout << "\ntotal sum of words:\n";
    std::cout << counter.size() << '\n';

    std::cout << "\ndoes stream have words:\n";
    std::cout << "banana: " << (counter.hasWord("banana") ? "yes" : "no") << '\n';
    std::cout << "circumambulate: " << (counter.hasWord("circumambulate") ? "yes" : "no") << '\n';

    // 5. iterate over word counter by frequency
    start_time = std::chrono::high_resolution_clock::now();
    for (auto it = counter.freqBegin(); it != counter.freqEnd(); it++)
    {
        *it;
        // std::cout << *it << '\n';
    }
    end_time = std::chrono::high_resolution_clock::now();
    time = end_time - start_time;
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