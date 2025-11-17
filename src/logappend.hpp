#ifndef LOGAPPEND
#define LOGAPPEND

#include "common.hpp"

/**
 * Implementations following: https://course.ece.cmu.edu/~ece732/s24/homework/bibifi/logappend.html
 */

/*
targetName is guest/employee name, and isEmployee identifies if that name belongs to an employee (true) or guest (false)
*/
int logWrite(const std::string logFileName, const std::string targetName, bool isEmployee,
     unsigned int roomId, bool isArrival, unsigned int timestamp = 1);

#endif