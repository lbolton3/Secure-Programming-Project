#include "logappend.hpp"

int logWrite(const std::string logFileName, const std::string employeeName, const std::string guestName, unsigned int roomId, bool isArrival){
    /* VALIDATION */

    // regex matches any: '..' or '\' or '/' 
    // prevent file directory traversal
    std::regex invalidFileNameParts(R"(\.\.|\\|\/)"); 
    if(std::regex_search(logFileName, invalidFileNameParts)){
        std::cout << "invalid" << std::endl;
        return 255; // error code
    }

    // guest and employee names
    // must be A-Z and a-z only, no spaces
    std::regex invalidName(R"(^[A-Za-z]+$)"); 
    if(!std::regex_match(employeeName, invalidName)){
        std::cout << "invalid" << std::endl;
        return 255;
    }
    else if(!std::regex_match(guestName, invalidName)){
        std::cout << "invalid" << std::endl;
        return 255;
    }

    std::ofstream f(logFileName, std::ios::app);

    return 0; 
}

int main(){
    std::cout << "this is logappend" << std::endl;

    logWrite("test.txt", "aFFFF", "bdqwCdqw", 1, false);

    return 0;
}