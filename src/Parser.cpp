#include "Parser.h"

#include <vector>
#include <thread>
#include <string>
#include <cstring>

int Parser::findUniqueWords(const char *buf, size_t size)
{
    if (size == 0) return 0;

    const unsigned threadCount{std::thread::hardware_concurrency()};

    // When thread "magic" is not applicable
    const auto minChunk{1024};
    if (size < minChunk * threadCount) {
        parse(buf, buf + size);
        return words.size();
    }

    // TODO: move one chunk to the main thread
    std::vector<std::thread> threads;
    auto* left = buf;
    auto* end = buf + size;
    const auto chunk{size / threadCount};

    for (size_t i{}; i < threadCount; ++i) {
        auto size = left + chunk;
        auto* right = size > end ? end : size;

        // Trick to make sure chunk is aligned by word's edge
        // NOTE: will drastically drop perf for long words!
        while (right != end && *right != delimeter) { right++; }

        threads.emplace_back(&Parser::parse, this, left, right);

        if (right == end) break;
        left = right + 1;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return words.size();
}

void Parser::parse(const char* start, const char* end)
{
    for (const char* ptr = start; ptr < end; ++ptr) {
        start = ptr;
        ptr = static_cast<const char*>(memchr(ptr, delimeter, end - ptr));
        unsigned long strSize = (ptr ? ptr : end) - start;

        const std::string word{start, strSize};
        if (words.find(word) == words.end()) {
            std::lock_guard<std::mutex> lock(mutex);
            words.insert(word);
        }

        if (!ptr) break;
    }
}
