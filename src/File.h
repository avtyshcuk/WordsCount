#pragma once

#include <cstddef>

class File {
public:
    explicit File(const char* path);
    ~File();
    size_t size() const { return mSize; }
    char* buffer() const { return mBuffer; }
private:
    int mUnixFileDesc{-1};
    void* mWinHandler{};
    void* mWinMapping{};
    size_t mSize{};
    char* mBuffer{};
};
