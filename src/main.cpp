#include <chrono>
#include <iostream>

#include "File.h"
#include "Parser.h"

void usage(const std::string& programName)
{
    std::cout << "Usage: " << programName << " SOURCE" << std::endl;
}

int main(int argc, char* argv[]) try
{
    if (argc != 2) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();

    File file{argv[1]};
    Parser parser{};
    std::cout << "Unique words count: "
              << parser.findUniqueWords(file.buffer(), file.size())
              << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Total processing time: " << duration.count() << " ms" << std::endl;

    return EXIT_SUCCESS;

} catch (const std::exception& e) {
    std::cout << "main() failed: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
