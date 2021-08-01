#pragma once

#include <cstddef>
#include <mutex>
#include <unordered_set>
#include <string>

class Parser
{
public:
    int findUniqueWords(const char* buf, size_t size);

private:
    void parse(const char* start, const char* end);

private:
    std::unordered_set<std::string> words;
    std::mutex mutex{};
    // NOTE: hardcoded for simplicity, in case if flexibility needed
    // strtok may be used instead of relatively "fast" memchr function
    char delimeter{' '};
};

