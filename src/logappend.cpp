#include "logappend.hpp"
#include <openssl/rand.h>

int logWrite(const std::string logFileName, const std::string targetName, bool isEmployee, unsigned int roomId, bool isArrival,
    unsigned int timestamp, const std::string& token) {

    /* VALIDATION */
    
    // regex matches any: '..' or '\' or '/' 
    // prevent file directory traversal
    std::regex invalidFileNameParts(R"(\.\.|\\|^\/)"); 
    if(std::regex_search(logFileName, invalidFileNameParts)){
        return 255; // error code
    }

    // guest and employee names
    // must be A-Z and a-z only, no spaces
    std::regex invalidName(R"(^[A-Za-z]+$)"); 
    if(!std::regex_match(targetName, invalidName)){
        return 255;
    }

    // validate timestamp, according to spec must be can't be 0
    if(timestamp == 0){
        return 255;
    }

    // validate token is not empty
    if(token.empty()){
        return 255;
    }

    /* ENCRYPTION LOGIC */

    bool fileExists = std::ifstream(logFileName).good();
    unsigned char salt[16];
    unsigned char key[32];
    
    if(!fileExists){
        RAND_bytes(salt, 16);
        std::ofstream outFile(logFileName, std::ios::binary);
        outFile.write((char*)salt, 16);
        outFile.close();
    } else {
        std::ifstream inFile(logFileName, std::ios::binary);
        inFile.read((char*)salt, 16);
        if(inFile.gcount() != 16){
            std::cerr << "integrity violation" << std::endl;
            return 255;
        }
        inFile.close();
    }
    
    deriveKey(token, key, salt);

    // Creating the log entry
    std::string entry = "[" + std::to_string(timestamp) + "] room \"" + 
                        std::to_string(roomId) + "\": " +
                        (isEmployee ? "employee" : "guest") + " \"" + 
                        targetName + "\" " + 
                        (isArrival ? "arrived" : "departed") + "\n";

    std::string encryptedEntry = encryptData(entry, key);
    
    
    std::ofstream outFile(logFileName, std::ios::binary | std::ios::app);
    outFile.write(encryptedEntry.data(), encryptedEntry.size());
    outFile.close();
    
    return 0;
}