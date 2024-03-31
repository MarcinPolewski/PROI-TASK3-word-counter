#include "word_counter.h"
#include <fstream>

int main()
{

    word_counter wc = word_counter();
    std::string s1 = "baba", s2 = "gaga";
    wc.addWord(s1);
    wc.addWord(s2);

    std::cout << wc;

    // std::cout << "start\n";

    // std::ofstream fileHandle("counterOutput.txt");

    // fileHandle << "test";

    // fileHandle.close();

    // std::cout << "end\n";

    return 0;
}