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
std::map<std::string, std::string> parseArguments(int argc, char* argv[]);

#endif 