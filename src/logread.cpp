#include "logread.hpp"

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
std::vector<std::vector<std::string>> parseLog(const std::string& logFileName) {
    // Open Log File
    std::ifstream file(logFileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << logFileName << std::endl;
        return {};
    }

    std::string line;
    std::vector<std::vector<std::string>> logEntries;
    
    //log format : [TIMESTAMP] room "ROOMID": (guest | employee) "NAME" (arrived | departed)
    std::regex logEntryRegex(R"(\[\d+\] room \"(\d+)\": (employee|guest) \"([A-Za-z]+)\" (arrived|departed))");
    
    // Read Log File Line by Line
    while (std::getline(file, line)) {
        std::smatch matches;
        if (std::regex_search(line, matches, logEntryRegex)) {
            
            std::string roomID = matches[1];
            std::string entryRole = matches[2];
            std::string name = matches[3];
            std::string action = matches[4];

            logEntries.push_back({roomID, entryRole, name, action});
        }
    }

    file.close();
    return logEntries;
}


// Function to get current attendants (employees or guests)
// INPUT: log file name, role ("employee" or "guest")
// OUTPUT: prints the names of current attendants of the specified role
void printAttendants(const std::string& logFileName, const std::string& role) {
    auto logEntries = parseLog(logFileName);
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
void printOccupiedRooms(const std::string& logFileName) {
    auto logEntries = parseLog(logFileName);
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
void printRoomHistory(const std::string& logFileName, const std::string& attendantName) {
    auto logEntries = parseLog(logFileName);
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
