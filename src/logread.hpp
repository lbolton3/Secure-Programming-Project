#ifndef LOGREAD
#define LOGREAD

#include "common.hpp"

// declarations 
std::vector<std::vector<std::string>> parseLog(const std::string& logFileName, const std::string& token);

void printAttendants(const std::string& logFileName, const std::string& role, const std::string& token);

void printOccupiedRooms(const std::string& logFileName, const std::string& token);
void printRoomHistory(const std::string& logFileName, const std::string& attendantName, const std::string& token);

#endif