#include <gtest/gtest.h>
#include "entry.h"
#include "word_counter.h"

TEST(entry, default_contructor)
{
    entry a = entry();
    // testing if does not throw an error
}

TEST(entry, constructor_and_getters_1)
{
    std::string s = "baba";
    entry e = entry(s);

    ASSERT_EQ(int(e), 1);
    std::string expected = "baba";
    ASSERT_EQ(*e, expected);
}

TEST(entry, constructor_and_getters_2)
{
    std::string s = "baba";
    entry e = entry(s, 10);

    ASSERT_EQ(int(e), 10);
    std::string expected = "baba";
    ASSERT_EQ(*e, expected);
}

TEST(entry, constructor_invalid_value)
{
    std::string s = "baba";
    entry e;
    ASSERT_THROW(e = entry(s, 0), std::invalid_argument);
    ASSERT_THROW(e = entry(s, -2), std::invalid_argument);
}

TEST(entry, getString)
{
    std::string s = "baba";
    entry e = entry(s, 5);
    ASSERT_EQ(e.getString(), "[baba,5]");
}

TEST(entry, outputStream)
{
    std::string s = "baba";
    entry e = entry(s, 5);

    std::stringstream ss;
    std::stringstream expected;
    expected << "[baba,5]";
    ss << e;
    ASSERT_EQ(ss.str(), expected.str());
}

TEST(entry, inputStream_1)
{
    std::stringstream input;
    input << "[baba,5]";
    entry e;

    input >> e;
    ASSERT_EQ((int)e, 5);
    ASSERT_EQ(*e, "baba");
}

TEST(entry, inputStream_invalid_structure_no_comma)
{
    std::stringstream input;
    input << "[baba5]";
    entry e;

    ASSERT_THROW(input >> e, std::runtime_error);
}

TEST(entry, inputStream_no_first_value)
{
    std::stringstream input;
    input << "[,5]";
    entry e;

    ASSERT_THROW(input >> e, std::runtime_error);
}

TEST(entry, inputStream_no_last_value)
{
    std::stringstream input;
    input << "[baba,]";
    entry e;

    ASSERT_THROW(input >> e, std::runtime_error);
}

TEST(entry, inputStream_no_bracket_1)
{
    std::stringstream input;
    input << "baba5]";
    entry e;

    ASSERT_THROW(input >> e, std::runtime_error);
}

TEST(entry, inputStream_no_bracket_2)
{
    std::stringstream input;
    input << "[baba5";
    entry e;

    ASSERT_THROW(input >> e, std::runtime_error);
}

TEST(entry, inputStream_no_numer_as_count)
{
    std::stringstream input;
    input << "[baba,a]";
    entry e;

    ASSERT_THROW(input >> e, std::runtime_error);
}

TEST(entry, addAndSaveOperator)
{
    std::string s1 = "baba";
    entry e1 = entry(s1, 1);
    std::string s2 = "baba";
    entry e2 = entry(s2, 2);

    e1 += e2;
    ASSERT_EQ((int)e1, 3);
    ASSERT_EQ((int)e2, 2);
}

TEST(entry, addAndSaveOperator_other_values)
{
    std::string s1 = "baba";
    entry e1 = entry(s1, 1);
    std::string s2 = "gaga";
    entry e2 = entry(s2, 2);

    ASSERT_THROW(e1 += e2, std::invalid_argument);
}

TEST(entry, greater_and_lesser_operator_1)
{
    std::string s1 = "aaa";
    entry e1 = entry(s1, 1);
    std::string s2 = "aaa";
    entry e2 = entry(s2, 2);

    ASSERT_TRUE(e1 < e2);
    ASSERT_FALSE(e1 > e2);
}

TEST(entry, greater_and_lesser_operator_2)
{
    std::string s1 = "aaa";
    entry e1 = entry(s1, 1);
    std::string s2 = "bbb";
    entry e2 = entry(s2, 2);

    ASSERT_TRUE(e1 < e2);
    ASSERT_FALSE(e1 > e2);
}

TEST(entry, greater_and_lesser_operator_3)
{
    std::string s1 = "aaa";
    entry e1 = entry(s1, 2);
    std::string s2 = "bbb";
    entry e2 = entry(s2, 2);

    ASSERT_FALSE(e1 < e2);
    ASSERT_FALSE(e1 > e2);
}

TEST(findLastComma, test1)
{
    std::string s = "[baba,1]";
    ASSERT_EQ(findLastComma(s), 5);
}

TEST(findLastComma, test2)
{
    std::string s = "[b,a,ba,1]";
    ASSERT_EQ(findLastComma(s), 7);
}

TEST(findLastComma, test3)
{
    std::string s = "[b,,ba1]";
    ASSERT_EQ(findLastComma(s), 3);
}

TEST(findLastComma, test_no_comma)
{
    std::string s = "[bba1]";
    ASSERT_EQ(findLastComma(s), -1);
}

TEST(word_counter, init_and_getters_1)
{
    // testing if does not throw an error
    word_counter w = word_counter();
}

TEST(word_counter, init_and_getter_2)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 2);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};

    word_counter wc = word_counter(arr);
    ASSERT_EQ(wc.isEmpty(), false);
    ASSERT_EQ(wc.getList()[0] == e1, true);
    ASSERT_EQ(wc.getList()[1] == e2, true);
    ASSERT_EQ(wc.getList()[2] == e3, true);
}

TEST(word_counter, getIdx)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 2);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};

    word_counter wc(arr);
    ASSERT_EQ(wc.getIdx(s1), 0);
    ASSERT_EQ(wc.getIdx(s2), 1);
    ASSERT_EQ(wc.getIdx(s3), 2);

    std::string s4 = "ggg";
    ASSERT_EQ(wc.getIdx(s4), -1);
}

TEST(word_counter, getEntryReference)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 2);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};

    word_counter wc(arr);
    ASSERT_EQ(wc.getEntryReference(s3) == e3, true);
    ASSERT_EQ(wc.getEntryReference(s2) == e2, true);
    ASSERT_EQ(wc.getEntryReference(s1) == e1, true);

    std::string s4 = "ggg";
    ASSERT_THROW(wc.getEntryReference(s4), std::runtime_error);
}

TEST(word_counter, isEmpty)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 2);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};

    word_counter wc;
    ASSERT_TRUE(wc.isEmpty());

    wc.addWords(arr);
    ASSERT_TRUE(!wc.isEmpty());
}

TEST(word_counter, hasWord)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 2);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    ASSERT_TRUE(wc.hasWord(s1));
    ASSERT_TRUE(wc.hasWord(s2));
    ASSERT_TRUE(wc.hasWord(s3));

    std::string s4 = "ddd";
    ASSERT_TRUE(!wc.hasWord(s4));
}

TEST(word_counter, highestLowestCount)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 20);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    ASSERT_TRUE(wc.highesCount() == e2);
    ASSERT_TRUE(wc.lowestCount() == e1);
}

TEST(word_counter, numberOfWords)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 20);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    ASSERT_EQ(wc.numberOfWords(), 24);
}

TEST(word_counter, getList)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 20);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    ASSERT_TRUE(wc.getList()[0] == e1);
    ASSERT_TRUE(wc.getList()[1] == e2);
    ASSERT_TRUE(wc.getList()[2] == e3);
}

TEST(word_counter, addWord)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 20);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    std::string s4 = "aba";
    wc.addWord(s4);

    ASSERT_TRUE(wc.getList()[0] == e1);
    ASSERT_TRUE(*wc.getList()[1] == s2);
    ASSERT_TRUE(wc.getList()[2] == e3);
    ASSERT_TRUE(*wc.getList()[3] == s4);
    ASSERT_TRUE((int)wc.getList()[3] == 1);
}

TEST(word_counter, addWords_from_vector_of_strings)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 20);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    std::string s4 = "aba";
    std::string s5 = "eee";
    std::string s6 = "aaa";

    std::vector<std::string> wordsToAdd = {s4, s5, s6};
    wc.addWords(wordsToAdd);

    ASSERT_TRUE(*wc.getList()[0] == s1);
    ASSERT_TRUE((int)wc.getList()[0] == 1);

    ASSERT_TRUE(*wc.getList()[1] == s2);
    ASSERT_TRUE((int)wc.getList()[1] == 20);

    ASSERT_TRUE(*wc.getList()[2] == s3);
    ASSERT_TRUE((int)wc.getList()[2] == 4);

    ASSERT_TRUE(*wc.getList()[3] == s4);
    ASSERT_TRUE((int)wc.getList()[3] == 1);

    ASSERT_TRUE(*wc.getList()[4] == s5);
    ASSERT_TRUE((int)wc.getList()[3] == 1);
}

TEST(word_counter, addWords_from_vector_of_entries)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 20);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    std::string s4 = "aba";
    entry e4(s4, 5);
    std::string s5 = "eee";
    entry e5(s5, 7);
    std::vector<entry> wordsToAdd = {e4, e5};
    wc.addWords(wordsToAdd);

    ASSERT_TRUE(wc.getList()[0] == e1);
    ASSERT_TRUE(wc.getList()[1] == e2);
    ASSERT_TRUE(wc.getList()[2] == e3);
    ASSERT_TRUE(wc.getList()[3] == e4);
    ASSERT_TRUE(wc.getList()[4] == e5);
}

TEST(word_counter, addWords_from_stream)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 20);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    std::stringstream ss;

    ss << "aaa "
       << "zzz "
       << "bbb "
       << "aba ";
    wc.addWords(ss);

    ASSERT_TRUE(*wc.getList()[0] == "ccc");
    ASSERT_TRUE((int)wc.getList()[0] == 1);

    ASSERT_TRUE(*wc.getList()[1] == "bbb");
    ASSERT_TRUE((int)wc.getList()[1] == 21);

    ASSERT_TRUE(*wc.getList()[2] == "aaa");
    ASSERT_TRUE((int)wc.getList()[2] == 4);

    ASSERT_TRUE(*wc.getList()[3] == "zzz");
    ASSERT_TRUE((int)wc.getList()[3] == 1);

    ASSERT_TRUE(*wc.getList()[4] == "aba");
    ASSERT_TRUE((int)wc.getList()[4] == 1);
}

TEST(word_counter, clearCounter)
{
    std::string s1 = "ccc";
    entry e1(s1, 1);
    std::string s2 = "bbb";
    entry e2(s2, 20);
    std::string s3 = "aaa";
    entry e3(s3, 3);

    std::vector<entry> arr = {e1, e2, e3};
    word_counter wc(arr);

    wc.clearCounter();
    ASSERT_TRUE(wc.isEmpty());
}

TEST(word_counter, addAndSaveOperator)
{
    std::string s1 = "aaa";
    entry e1(s1, 1);
    std::string s2 = "ccc";
    entry e2(s2, 20);

    std::string s3 = "aaa";
    entry e3(s3, 3);
    std::string s4 = "bbb";
    entry e4(s4, 7);

    std::vector<entry> arr1 = {e1, e2};
    std::vector<entry> arr2 = {e3, e4};
    word_counter wc1(arr1);
    word_counter wc2(arr2);

    wc1 += wc2;

    ASSERT_TRUE(*wc1.getList()[0] == "aaa");
    ASSERT_TRUE((int)wc1.getList()[0] == 4);

    ASSERT_TRUE(*wc1.getList()[1] == "ccc");
    ASSERT_TRUE((int)wc1.getList()[1] == 20);

    ASSERT_TRUE(*wc1.getList()[2] == "bbb");
    ASSERT_TRUE((int)wc1.getList()[2] == 7);
}

TEST(word_counter, alpha_iterator)
{
    ASSERT_TRUE(false);
}

TEST(word_counter, freq_iterator)
{
    ASSERT_TRUE(false);
}