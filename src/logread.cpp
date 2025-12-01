#include "logread.hpp"
#include "common.hpp"
// Usage:
// logread -K <token> -S <log>
// logread -K <token> -R (-E <name> | -G <name>) <log>
// Optional Usage
// logread -K <token> -T (-E <name> | -G <name>) <log>
// logread -K <token> -I (-E <name> | -G <name>) [(-E <name> | -G <name>) ...] <log>

// Simple Testing Commands:
// g++ logread.cpp -o logread; ./logread.exe -K token -S log.txt
// g++ logread.cpp -o logread; ./logread.exe -K token -R -E Charlie log.txt
// g++ logread.cpp -o logread; ./logread.exe -K token -R -G David log.txt


// Function to parse the log file and return entries
// INPUT: log file name
// OUTPUT: vector of vectors containing log entries
//        each entry is a vector of strings: [roomID, role, name, action]
std::vector<std::vector<std::string>> parseLog(const std::string& logFileName, const std::string& token) {
    std::ifstream file(logFileName, std::ios::binary);
    if (!file.is_open()) {
        return {};
    }

    unsigned char salt[16];
    file.read((char*)salt, 16);
    if(file.gcount() != 16){
        return {}; 
    }

    unsigned char key[32];
    deriveKey(token, key, salt);

    std::vector<std::vector<std::string>> logEntries;
    
    std::regex logEntryRegex(R"(\[\d+\] room \"(\d+)\": (employee|guest) \"([A-Za-z]+)\" (arrived|departed))");

    while (true) {
        int entrySize = 0;
        file.read(reinterpret_cast<char*>(&entrySize), sizeof(entrySize));

        if (file.eof() || file.gcount() == 0) {
            break; 
        }

        std::vector<char> encryptedBytes(entrySize);

        file.read(encryptedBytes.data(), entrySize);
    
        if (file.gcount() != entrySize) {
            std::cerr << "Integrity violation: Log entry incomplete." << std::endl;
            return {};
        }

        std::string encryptedString(encryptedBytes.begin(), encryptedBytes.end());
        std::string decryptedData = decryptData(encryptedString, key);
        
        if(decryptedData.empty()){
            std::cerr << "Integrity violation: Decryption failed." << std::endl;
            return {};
        }

        std::smatch matches;
        if (std::regex_search(decryptedData, matches, logEntryRegex)) {
            std::string roomID = matches[1];
            std::string entryRole = matches[2];
            std::string name = matches[3];
            std::string action = matches[4];
            logEntries.push_back({roomID, entryRole, name, action});
        }
    }

    return logEntries;
}


// Function to get current attendants (employees or guests)
// INPUT: log file name, role ("employee" or "guest")
// OUTPUT: prints the names of current attendants of the specified role
void printAttendants(const std::string& logFileName, const std::string& role, const std::string& token) {
    auto logEntries = parseLog(logFileName, token);
    std::set<std::string> attendants;

    for (const auto& entry : logEntries) {
        std::string entryRole = entry[1];
        std::string name = entry[2];
        std::string action = entry[3];

        if (entryRole == role) {
            if (action == "arrived") {
                attendants.insert(name);
            } else if (action == "departed") {
                attendants.erase(name);
            }
        }
    }

    for (const auto& attendant : attendants) {
        std::cout << attendant;
        if (attendant != *attendants.rbegin()) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}


// Function to get occupied rooms and their occupants
// INPUT: log file name
// OUTPUT: prints each occupied room and its occupants
void printOccupiedRooms(const std::string& logFileName, const std::string& token) {
    auto logEntries = parseLog(logFileName, token);
    std::map<std::string, std::set<std::string>> rooms;

    for (const auto& entry : logEntries) {
        std::string roomID = entry[0];
        std::string name = entry[2];
        std::string action = entry[3];

        if (action == "arrived") {
            rooms[roomID].insert(name);
        } else if (action == "departed") {
            rooms[roomID].erase(name);
        }
    }

    // Print Occupied Rooms and their Occupants
    for (const auto& room : rooms) {
        if (room.second.empty()) {
            continue;
        }
        std::cout << room.first << ": ";
        for (const auto& occupant : room.second) {
            std::cout << occupant;
            if (occupant != *room.second.rbegin()) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
}


// Function to print room history for a specific attendant
// INPUT: log file name, attendant name
// OUTPUT: prints the list of room IDs the attendant has entered
void printRoomHistory(const std::string& logFileName, const std::string& attendantName, const std::string& token) {
    auto logEntries = parseLog(logFileName, token);
    std::vector<std::string> roomHistory;

    for (const auto& entry : logEntries) {
        std::string entryRoomID = entry[0];
        std::string name = entry[2];
        std::string action = entry[3];

        if (name == attendantName && action == "arrived") {
            roomHistory.push_back(entryRoomID);
        }
    }

    for (const auto& roomID : roomHistory) {
        std::cout << roomID;
        if (roomID != roomHistory.back()) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}
