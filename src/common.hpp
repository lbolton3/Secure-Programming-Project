#ifndef COMMON 
#define COMMON 
#include <iostream> 
#include <fstream> 
#include <regex> 
#include <map> 
#include <string> 
#include <openssl/sha.h> 
#include <iomanip> 
#include <set>
#include <vector>

// INPUT: Command-line arguments, consiting of flags (starting with '-') and their values, and the log file 
// OUTPUT: A map of flags to their values, and the log file // - If a flag does not have a value, it is assigned "true"
std::map<std::string, std::string> parseArguments(int argc, char* argv[]); 

// UTILITY FUNCTIONS: 
// used to split the commands that are received as input from a batch file to feed to the parser 
std::vector<std::string> splitString(const std::string& s, char delimiter); 

// debug function used for logging the result of parseArguments 
void printArgs(std::map<std::string, std::string> args); 

// CRYPTO FUNCTIONS 
std::string sha256(const std::string s); 

// Hashes and compares the passed token to the hashed authentication token
bool validateToken(const std::string);

void deriveKey(const std::string& token, unsigned char* key, const unsigned char* salt);
std::string encryptData(const std::string& plaintext, const unsigned char* key);
std::string decryptData(const std::string& encrypted, const unsigned char* key);
#endif