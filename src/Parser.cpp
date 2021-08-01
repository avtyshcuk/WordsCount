#include "Parser.h"

#include <algorithm>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

int Parser::findUniqueWords(const char *buf, size_t size)
{
    if (size == 0) return 0;

    unsigned threadCount{std::thread::hardware_concurrency()};

    // When thread "magic" is not applicable
    const auto minChunk{1024};
    if (size < minChunk * threadCount) {
        threadCount = 1;
    }

    // TODO: move one chunk to the main thread
    std::vector<std::thread> threads;
    auto* left = buf;
    auto* end = buf + size;
    const auto chunkSize{size / threadCount};

    while (threadCount > 0 && left < end) {
        auto* right = std::min(left + chunkSize, end);

        // Trick to make sure chunk is aligned by word's edge
        // NOTE: will drastically drop perf for long words!
        right = std::find(right, end, delimeter);

        threads.emplace_back(&Parser::parse, this, left, right);

        left = right + 1;
        --threadCount;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return words.size();
}

void Parser::parse(const char* start, const char* end)
{
    while (start && start < end) {
        auto* localEnd = static_cast<const char*>(memchr(start, delimeter, end - start));
        unsigned long strSize = (localEnd ? localEnd : end) - start;

        const std::string word{start, strSize};
        if (words.find(word) == words.end()) {
            std::lock_guard<std::mutex> lock(mutex);
            words.insert(word);
        }

        start += strSize + 1;
    }
}
