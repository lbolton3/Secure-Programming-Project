#include <cassert>
#include <iostream>
#include <string>

#include "../src/common.hpp"
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
    assert(255 == logWrite(payload, "dummyEmployee", "dummyGuest", 1, true));
    
    payload = "./../../../etc/passwd";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyEmployee", "dummyGuest", 1, true));

    payload = "/etc/passwd";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyEmployee", "dummyGuest", 1, true));

    payload = "directory/../secretfiles/myfile.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyEmployee", "dummyGuest", 1, true));

    payload = "./directory/../secretfiles/myfile.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyEmployee", "dummyGuest", 1, true));

    cout << endl; 
    cout << "Testing non-malicious file paths" << endl;

    payload = "file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(0 == logWrite(payload, "dummyEmployee", "dummyGuest", 1, true));

    payload = "./file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(0 == logWrite(payload, "dummyEmployee", "dummyGuest", 1, true));

    payload = "./directory/file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(0 == logWrite(payload, "dummyEmployee", "dummyGuest", 1, true));
}

int main(){
    cout << "----- TESTS FOR LOG WRITE FUNCTION -----" << endl << endl;

    cout << "[!] Testing Input Validation" << endl; 
    testInputValidation();
}