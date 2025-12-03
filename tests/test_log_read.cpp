#include <cassert>
#include <iostream>
#include <string>

#include "../src/logread.hpp"
#include "../src/logappend.hpp"

using namespace std;


// ---- HELPER FUNCTIONS ----
void generateSampleLogFile(const string& logFileName, const string& AUTH_TOKEN) {
    // //Create Log File

    // Remove existing log file if it exists
    remove(logFileName.c_str()); 

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

    cout << "Log file '" << logFileName << "' generated successfully." << endl << endl;
}

string captureOutput(function<void()> func) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    func();

    cout.rdbuf(old);
    return buffer.str();
}

// ---- TEST FUNCTIONS ----

// for now this only generates a log for us to manually test on
int main(int argc, char* argv[]){
    if (argc < 2) {
        cout << "testlogread requires the security token. Usage: \"make testlogread TOKEN=?\" replace ? with the token." << endl;
        return 1;
    }

    string token = argv[1];
    if(!validateToken(token)){
        cout << "invalid token." << endl;
        return 1;
    }

    cout << endl << "----- TESTS FOR LOG READ -----" << endl << endl;

    // Generate Sample Log File
    generateSampleLogFile("logfile.txt", token);

    // Test Proper Log Parsing
    cout << "Testing proper log parsing" << endl;
    auto output = captureOutput([&]() {
        parseLog("logfile.txt", token);
    });
    assert(output.find("invalid") == string::npos);

    // Traversal Attack Test
    string invalidLogFileName = "../logfile.txt";
    cout << "Testing payload \"" << invalidLogFileName << "\"" << endl; 
    output = captureOutput([&]() {
        parseLog(invalidLogFileName, token);
    });
    assert(output.find("invalid") != string::npos);
    
    invalidLogFileName = "C:\\logfile.txt";
    cout << "Testing payload \"" << invalidLogFileName << "\"" << endl; 
    output = captureOutput([&]() {
        parseLog(invalidLogFileName, token);
    });
    assert(output.find("invalid") != string::npos);

    // Test invalid token
    string invalidToken = "wrongtoken";
    cout << "Testing invalid token \"" << invalidToken << "\"" << endl;
    output = captureOutput([&]() {
        parseLog("logfile.txt", invalidToken);
    });
    assert(output.find("invalid") != string::npos);

    cout << endl <<"----- All tests for log read passed -----" << endl << endl;
    return 0;
}