#include "logread.hpp"

// Example usage:
// logread -K <token> -S <log>
// logread -K <token> -R (-E <name> | -G <name>) <log>
// Optional usage
// logread -K <token> -T (-E <name> | -G <name>) <log>
// logread -K <token> -I (-E <name> | -G <name>) [(-E <name> | -G <name>) ...] <log>

// Simple setup
// g++ src/logread.cpp -o logread; ./logread.exe -K token -S log.txt



int main(int argc, char* argv[]) {
    std::cout << "this is logread" << std::endl;

    auto args = parseArguments(argc, argv);

    // Debug Argument Output
    std::cout << std::endl;
    std::cout << args.size() << " arguments found." << std::endl;
    std::cout << "Parsed Arguments:" << std::endl;
    for (const auto& pair : args) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Determine Operation
    if (args["-S"] != "") {
        std::cout << "FORMAT: logread -K <token> -S <log>" << std::endl;
        

    } else if (args["-R"] != "") {
        std::cout << "FORMAT: logread -K <token> -R (-E <name> | -G <name>) <log>" << std::endl;

    } else if (args["-T"] != "") {
        std::cout << "FORMAT: logread -K <token> -T (-E <name> | -G <name>) <log>" << std::endl;
        std::cout << "unimplemented" << std::endl;

    } else if (args["-I"] != "") {  
        std::cout << "FORMAT: logread -K <token> -I (-E <name> | -G <name>) [(-E <name> | -G <name>) ...] <log>" << std::endl;
        std::cout << "unimplemented" << std::endl;

    } else {
        std::cout << "No valid operation specified." << std::endl;
    }

    return 0;
}