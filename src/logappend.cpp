#include "logappend.hpp"

int logWrite(const std::string logFileName, const std::string targetName, bool isEmployee, unsigned int roomId, bool isArrival,
    unsigned int timestamp){
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

    std::ofstream f(logFileName, std::ios::app);

    f << "[" << timestamp << "] room \"" << roomId << "\": " << ( isEmployee ? "employee " : "guest ") << "\"" << targetName << "\" " << 
        (isArrival ? "arrived" : "departed") << "\n";

    f.close();

    return 0; 
}

/*
not needed anymore
*/

// int main(){
//     std::cout << "this is logappend" << std::endl;

//     int i = logWrite("test.txt", "MahaAllouzi", "MikhailNesterenko", 1, false, 123);

//     std::cout << i << std::endl;

//     return 0;
// }