#include <cassert>
#include <iostream>
#include <string>

#include "../src/logappend.hpp"

using namespace std;

const std::string AUTH_TOKEN = "123"; // for now just hardcoded to the correct token 

void testInputValidation(){
    cout << "Testing path traversal attacks..." << endl;
    string payload = "";

    // path traversal attacks
    payload = "../../../etc/passwd";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));
    
    payload = "./../../../etc/passwd";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));

    payload = "/etc/passwd";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));

    payload = "directory/../secretfiles/myfile.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));

    payload = "./directory/../secretfiles/myfile.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));
    
    // Should fail for subdirectory
    payload = "./directory/file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));
    
    // should be secure against windows specific paths traversal too
    payload = "E:\\backup.zip";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));

    cout << endl; 
    cout << "Testing non-malicious file paths..." << endl;

    payload = "file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(0 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));

    payload = "./file.txt";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(0 == logWrite(payload, "dummyName", false, 1, true, 1, AUTH_TOKEN));

    cout << endl; 
    cout << "Testing invalid timestamp..." << endl;

    int payloadTimestamp = 0;
    cout << "Testing payload \"" << payloadTimestamp << "\"" << endl; 
    assert(255 == logWrite("file.txt", "dummyName", true, 1, true, payloadTimestamp, AUTH_TOKEN));

    cout << endl; 
    cout << "Testing invalid guest and employee names..." << endl;

    payload = "Mikhail Nesterenko";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp, AUTH_TOKEN));

    payload = "Mikhail Nesterenko";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp, AUTH_TOKEN));
    
    payload = "Maha7";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp, AUTH_TOKEN));

    payload = "J0ao";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp, AUTH_TOKEN));

    payload = "Joao$";
    cout << "Testing payload \"" << payload << "\"" << endl; 
    assert(255 == logWrite("file.txt", payload, true, 1, true, payloadTimestamp, AUTH_TOKEN));
}

int main(){
    cout << "----- TESTS FOR LOG WRITE FUNCTION -----" << endl << endl;

    cout << "[!] Testing Input Validation" << endl; 
    testInputValidation();
}