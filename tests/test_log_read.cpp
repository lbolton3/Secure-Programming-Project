#include <cassert>
#include <iostream>
#include <string>

#include "../src/logread.hpp"
#include "../src/logappend.hpp"

using namespace std;

const std::string AUTH_TOKEN = "123"; // for now just hardcoded to the correct token 

// ---- HELPER FUNCTIONS ----
void generateSampleLogFile(const std::string& logFileName) {
    // //Create Log File

    logWrite(logFileName, "Alice", true, 101, true, 1001, AUTH_TOKEN);
    logWrite(logFileName, "Bob", false, 212, true, 1002, AUTH_TOKEN);
    logWrite(logFileName, "Charlie", true, 404, true, 1003, AUTH_TOKEN);
    logWrite(logFileName, "David", false, 303, true, 1004, AUTH_TOKEN);
    logWrite(logFileName, "Eli", false, 505, true, 1005, AUTH_TOKEN);
    logWrite(logFileName, "Alice", true, 101, false, 1006, AUTH_TOKEN);
    logWrite(logFileName, "Charlie", true, 404, false, 1007, AUTH_TOKEN);
    logWrite(logFileName, "Charlie", true, 606, true, 1008, AUTH_TOKEN);
    logWrite(logFileName, "Alice", true, 101, true, 1009, AUTH_TOKEN);
    logWrite(logFileName, "Eli", false, 505, false, 1010, AUTH_TOKEN);
    logWrite(logFileName, "Eli", false, 505, true, 1011, AUTH_TOKEN);
    logWrite(logFileName, "David", false, 303, false, 1012, AUTH_TOKEN);
    logWrite(logFileName, "David", false, 303, true, 1013, AUTH_TOKEN);
    logWrite(logFileName, "Bob", false, 212, false, 1014, AUTH_TOKEN);
    logWrite(logFileName, "Fiona", false, 707, true, 1015, AUTH_TOKEN);
    logWrite(logFileName, "Grace", false, 404, true, 1016, AUTH_TOKEN);
    logWrite(logFileName, "Charlie", true, 606, false, 1017, AUTH_TOKEN);
    logWrite(logFileName, "Hank", false, 808, true, 1018, AUTH_TOKEN);
    logWrite(logFileName, "Eli", false, 505, false, 1019, AUTH_TOKEN);
    logWrite(logFileName, "Ivan", false, 303, true, 1020, AUTH_TOKEN);
    logWrite(logFileName, "Grace", false, 404, false, 1021, AUTH_TOKEN);
    logWrite(logFileName, "Alice", true, 101, false, 1022, AUTH_TOKEN);
    logWrite(logFileName, "Alice", true, 101, true, 1023, AUTH_TOKEN);
    logWrite(logFileName, "Charlie", true, 909, true, 1024, AUTH_TOKEN);
    logWrite(logFileName, "Fiona", false, 707, false, 1025, AUTH_TOKEN);
    logWrite(logFileName, "Jack", false, 505, true, 1026, AUTH_TOKEN);
    logWrite(logFileName, "Ivan", false, 303, false, 1027, AUTH_TOKEN);
    logWrite(logFileName, "Karen", true, 404, true, 1028, AUTH_TOKEN);
    logWrite(logFileName, "Hank", false, 808, false, 1029, AUTH_TOKEN);
    logWrite(logFileName, "Jack", false, 505, false, 1030, AUTH_TOKEN);

    std::cout << "Log file '" << logFileName << "' generated successfully." << std::endl;
}

std::string captureOutput(std::function<void()> func) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    func();

    std::cout.rdbuf(old);
    return buffer.str();
}

// ---- TEST FUNCTIONS ----

// for now this only generates a log for us to manually test on
int main(){
    cout << "----- TESTS FOR LOG READ -----" << endl << endl;

    generateSampleLogFile("logfile");

    cout << endl <<"----- All tests for log read passed -----" << endl;
    return 0;
}