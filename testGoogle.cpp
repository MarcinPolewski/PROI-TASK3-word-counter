#include <gtest/gtest.h>
#include "entry.h"

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