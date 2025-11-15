#include <cassert>
#include <iostream>
#include <string>

#include "../src/logappend.hpp"

using namespace std;

/**
 * For now just compile and run manually:
 *  - g++ test_log_write.cpp ../src/logappend.cpp -o test_log_write
 *  - test_log_write.exe
 * 
 * Later we can make a python or batch script to auto run all the tests
 * We also need to cleanup after it, since it produces .exe and .txt files
 */

void testInputValidation(){
    cout << "Testing path traversal attacks..." << endl;
    string payload = "";

    // path traversal attacks
    payload = "../../../etc/passwd";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1));
    
    payload = "./../../../etc/passwd";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1));

    payload = "/etc/passwd";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1));

    payload = "directory/../secretfiles/myfile.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1));

    payload = "./directory/../secretfiles/myfile.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1));

    cout << endl; 
    cout << "Testing non-malicious file paths..." << endl;

    payload = "file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(0 == logWrite(payload, "dummyName", false, 1, true, 1));

    payload = "./file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(0 == logWrite(payload, "dummyName", false, 1, true, 1));

    payload = "./directory/file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(0 == logWrite(payload, "dummyName", false, 1, true, 1));

    cout << endl; 
    cout << "Testing invalid timestamp..." << endl;

    int payloadTimestamp = 0;
    cout << "Testing payload \"" << payloadTimestamp << "\"" << endl; 
    assert(255 == logWrite("file.txt", "dummyName", true, 1, true, payloadTimestamp));

    cout << endl; 
    cout << "Testing invalid guest and employee names..." << endl;

    payload = "Mikhail Nesterenko";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp));

    payload = "Mikhail Nesterenko";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp));
    
    payload = "Maha7";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp));

    payload = "J0ao";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp));

    payload = "Joao$";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp));
}

int main(){
    cout << "----- TESTS FOR LOG WRITE FUNCTION -----" << endl << endl;

    cout << "[!] Testing Input Validation" << endl; 
    testInputValidation();
}