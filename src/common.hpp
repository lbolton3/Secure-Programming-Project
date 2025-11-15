#ifndef COMMON
#define COMMON

#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <string>

// INPUT: Command-line arguments, consiting of flags (starting with '-') and their values, and the log file
// OUTPUT: A map of flags to their values, and the log file
//         - If a flag does not have a value, it is assigned "true"
std::map<std::string, std::string> parseArguments(int argc, char* argv[]) {
    std::map<std::string, std::string> arguments;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        // Check for the last argument (log file)
        if (i == argc-1) {
            if (arg[0] != '-') {
                std::string value = arg;
                arguments["log"] = value;
            }
        }

        // Process flags and their values
        if (arg[0] == '-') {
            std::string key = arg;
            std::string value;
            if ((i + 1) < argc && argv[i + 1][0] != '-') {
                value = argv[++i];
            } else {
                value = "true"; // Flag without value
            }
            arguments[key] = value;
        }
    }

    return arguments;
}

#endif 