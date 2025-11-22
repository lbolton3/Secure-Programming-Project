#ifndef LOGREAD
#define LOGREAD

#include "common.hpp"

// declarations 
std::vector<std::vector<std::string>> parseLog(const std::string& logFileName);

void printAttendants(const std::string& logFileName, const std::string& role);

void printOccupiedRooms(const std::string& logFileName);

void printRoomHistory(const std::string& logFileName, const std::string& attendantName);

#endif