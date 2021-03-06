#include "gtest/gtest.h"

#include <algorithm>
#include <cstdio>
#include <fstream>

#include "File.h"
#include "Parser.h"

class WordsCounterTest : public ::testing::Test
{
protected:
    void TearDown() override
    {
        remove(testFileName.c_str());
    }

    void prepareSimpleFile(const std::string& str)
    {
        std::ofstream file{testFileName};
        if (!file.is_open()) return;
        file << str;
    }

    void prepareComplexFile(const size_t size)
    {
        const size_t wordSize{testWord.size() + 1};
        const auto wordsCount{size / wordSize + 1};
        std::ofstream file{testFileName};
        if (!file.is_open()) return;

        std::string word{testWord};
        for (size_t i{}; i < wordsCount; ++i) {
            file << word << ' ';
            std::rotate(word.rbegin(), word.rbegin() + 1, word.rend());
        }
    }

protected:
    Parser parser;
    const std::string testFileName{"testfile"};
    const std::string testWord{"abcdefg"};
};

TEST_F(WordsCounterTest, parseEmptyFile)
{
    prepareSimpleFile("");
    File file{testFileName.c_str()};
    EXPECT_EQ(file.size(),  0);
}

TEST_F(WordsCounterTest, parseOneChar)
{
    prepareSimpleFile("a");
    File file{testFileName.c_str()};
    EXPECT_EQ(parser.findUniqueWords(file.buffer(), file.size()), 1);
}

TEST_F(WordsCounterTest, parseOneWord)
{
    prepareSimpleFile("word");
    File file{testFileName.c_str()};
    EXPECT_EQ(parser.findUniqueWords(file.buffer(), file.size()), 1);
}

TEST_F(WordsCounterTest, parseOnePhrase)
{
    prepareSimpleFile("a horse and a dog");
    File file{testFileName.c_str()};
    EXPECT_EQ(parser.findUniqueWords(file.buffer(), file.size()), 4);
}

TEST_F(WordsCounterTest, parseSmallFile)
{
    // With size about 1 MB
    prepareComplexFile(1e6);
    File file{testFileName.c_str()};
    EXPECT_EQ(parser.findUniqueWords(file.buffer(), file.size()), testWord.size());
}

TEST_F(WordsCounterTest, parseMidFile)
{
    // With size about 1 GB
    prepareComplexFile(1e9);
    File file{testFileName.c_str()};
    EXPECT_EQ(parser.findUniqueWords(file.buffer(), file.size()), testWord.size());
}

TEST_F(WordsCounterTest, parseLargeFile)
{
    // With size about 32 GB
    prepareComplexFile(32e9);
    File file{testFileName.c_str()};
    EXPECT_EQ(testWord.size(), parser.findUniqueWords(file.buffer(), file.size()));
}
