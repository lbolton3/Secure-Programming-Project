#ifndef LOGAPPEND
#define LOGAPPEND

#include "common.hpp"

/**
 * Implementations following: https://course.ece.cmu.edu/~ece732/s24/homework/bibifi/logappend.html
 */

/*
*/
int logWrite(const std::string logFileName, const std::string employeeName, const std::string guestName,
     unsigned int roomId, bool isArrival, unsigned int timestamp = 1);

#endif