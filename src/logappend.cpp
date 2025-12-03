#include "logappend.hpp"
#include <openssl/rand.h>

int logWrite(const std::string logFileName, const std::string targetName, bool isEmployee, unsigned int roomId, bool isArrival,
    unsigned int timestamp, const std::string& token) {
        
    /* VALIDATION */

    // regex matches any: '..' or '/' at the start or '\'
    // the last OR in this regex (?=([^/]*\/){2,}) matches if there are 2 or more '/' symbols
    // prevent file directory traversal
    std::regex invalidFileNameParts(R"(\.\.|\\|^\/|(?=([^/]*\/){2,}))"); 
    if(std::regex_search(logFileName, invalidFileNameParts)){
        return 255; 
    }
    
    // guest and employee names
    // must be A-Z and a-z only, no spaces
    std::regex invalidName(R"(^[A-Za-z]+$)"); 
    if(!std::regex_match(targetName, invalidName)){
        return 255;
    }
    
    // according to specification timestep is > 0
    if(timestamp == 0 || token.empty()){
        return 255;
    }
    
    /* ENCRYPTION SETUP */
    unsigned char salt[16];
    unsigned char key[32];
    
    std::ifstream inFile(logFileName, std::ios::binary);
    bool isNewFile = true;
    
    if (inFile.is_open()) {
        inFile.read((char*)salt, 16);
        if (inFile.gcount() == 16) {
            isNewFile = false;
        }
        inFile.close();
    }
    
    if (isNewFile) {
        RAND_bytes(salt, 16);
        std::ofstream outFile(logFileName, std::ios::binary | std::ios::trunc);
        if (!outFile) return 255;
        outFile.write((char*)salt, 16);
        outFile.close();
    }
    
    deriveKey(token, key, salt);
    
    std::string entry = "[" + std::to_string(timestamp) + "] room \"" + 
    std::to_string(roomId) + "\": " +
    (isEmployee ? "employee" : "guest") + " \"" + 
    targetName + "\" " + 
    (isArrival ? "arrived" : "departed") + "\n";
    
    std::string encryptedEntry = encryptData(entry, key);
    
    std::ofstream outFile(logFileName, std::ios::binary | std::ios::app);
    if (!outFile) return 255;
    
    int entrySize = encryptedEntry.size();

    outFile.write(reinterpret_cast<char*>(&entrySize), sizeof(entrySize));
    
    outFile.write(encryptedEntry.data(), entrySize);
    
    outFile.close();
    
    return 0;
}