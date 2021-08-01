#include "../File.h"

#include <windows.h>
#include <stdexcept>

File::File(const char *path)
{
    mWinHandler = ::CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                                0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (mWinHandler == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("file open error");
    }

    LARGE_INTEGER file_size;
    if (::GetFileSizeEx(mWinHandler, &file_size) == 0) {
        throw std::runtime_error("file size check error");
    }
    mSize = file_size.QuadPart;

    // MSDN: Applications should test for files with a length of 0 (zero) and reject those files
    if (mSize == 0) {
        ::CloseHandle(mWinHandler);
        return;
    }

    mWinMapping = ::CreateFileMapping(mWinHandler, 0, PAGE_READONLY, 0, 0, 0);
    if (mWinMapping == nullptr) {
        ::CloseHandle(mWinHandler);
        throw std::runtime_error("memory mapping error");
    }

    mBuffer = static_cast<char *>(MapViewOfFile(mWinMapping, FILE_MAP_READ, 0, 0, mSize));
    if (mBuffer == nullptr) {
        ::CloseHandle(mWinMapping);
        ::CloseHandle(mWinHandler);
        throw std::runtime_error("memory mapping error");
    }
}

File::~File()
{
    ::CloseHandle(mWinMapping);
    ::CloseHandle(mWinHandler);
}
