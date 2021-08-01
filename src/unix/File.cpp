#include "File.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdexcept>

File::File(const char* path)
{
    mUnixFileDesc = open(path, O_RDONLY);
    if (mUnixFileDesc == -1) throw std::runtime_error("file open error");

    struct stat64 statbuf;
    if (fstat64(mUnixFileDesc, &statbuf) == -1) throw std::runtime_error("file size check error");

    mSize = statbuf.st_size;
    if (mSize == 0) {
        close(mUnixFileDesc);
        return;
    }

    mBuffer = static_cast<char*>(mmap(NULL, mSize, PROT_READ, MAP_PRIVATE, mUnixFileDesc, 0));
    if (mBuffer == MAP_FAILED) {
        mBuffer = nullptr;
        throw std::runtime_error("memory mapping error");
    }
}

File::~File()
{
    munmap(mBuffer, mSize);
    close(mUnixFileDesc);
}
