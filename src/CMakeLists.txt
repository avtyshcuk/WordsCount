add_library(FileLib File.h)
if (WIN32)
    target_sources(FileLib
        PRIVATE win32/File.cpp
    )
endif()
if (UNIX)
    target_sources(FileLib
        PRIVATE unix/File.cpp
    )
endif()
add_library(ParserLib Parser.h Parser.cpp)
target_link_libraries(ParserLib pthread)

add_executable(WordsCounter main.cpp)
target_link_libraries(WordsCounter FileLib ParserLib)
