#include "logread.hpp"

// Example usage:
// logread -K <token> -S <log>
// logread -K <token> -R (-E <name> | -G <name>) <log>

// Simple setup
// g++ src/logread.cpp -o logread; ./logread.exe -K token -S log.txt



int main(int argc, char* argv[]) {
    std::cout << "this is logread" << std::endl;

    auto args = parseArguments(argc, argv);

    // Debug Argument Output
    std::cout << std::endl;
    std::cout << args.size() << " arguments found.\n";
    std::cout << "Parsed Arguments:\n";
    for (const auto& pair : args) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }




    return 0;
}