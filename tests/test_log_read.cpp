#include <cassert>
#include <iostream>
#include <string>

#include "../src/logread.hpp"

using namespace std;

/**
 * For now just compile and run manually:
 * g++ test_log_read.cpp -o test_log_read; ./test_log_read.exe
 *
 * Later we can make a python or batch script to auto run all the tests
 * We also need to cleanup after it, since it produces .exe and .txt files
 */

// ---- HELPER FUNCTIONS ----
void generateSampleLogFile(const std::string& logFileName) {
    //Create Log File
    std::ofstream file(logFileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << logFileName << std::endl;
        return;
    }

    //Write Sample Log Entries
    file << "[1001] room \"101\": employee \"Alice\" arrived\n";
    file << "[1002] room \"212\": guest \"Bob\" arrived\n";
    file << "[1003] room \"404\": employee \"Charlie\" arrived\n";
    file << "[1004] room \"303\": guest \"David\" arrived\n";
    file << "[1005] room \"505\": guest \"Eli\" arrived\n";
    file << "[1006] room \"101\": employee \"Alice\" departed\n";
    file << "[1007] room \"404\": employee \"Charlie\" departed\n";
    file << "[1008] room \"606\": employee \"Charlie\" arrived\n";
    file << "[1009] room \"101\": employee \"Alice\" arrived\n";
    file << "[1010] room \"505\": guest \"Eli\" departed\n";
    file << "[1011] room \"505\": guest \"Eli\" arrived\n";
    file << "[1012] room \"303\": guest \"David\" departed\n";
    file << "[1013] room \"303\": guest \"David\" arrived\n";
    file << "[1014] room \"212\": guest \"Bob\" departed\n";
    file << "[1015] room \"707\": guest \"Fiona\" arrived\n";
    file << "[1016] room \"404\": guest \"Grace\" arrived\n";
    file << "[1017] room \"606\": employee \"Charlie\" departed\n";
    file << "[1018] room \"808\": guest \"Hank\" arrived\n";
    file << "[1019] room \"505\": guest \"Eli\" departed\n";
    file << "[1020] room \"303\": guest \"Ivan\" arrived\n";
    file << "[1021] room \"404\": guest \"Grace\" departed\n";
    file << "[1022] room \"101\": employee \"Alice\" departed\n";
    file << "[1023] room \"101\": employee \"Alice\" arrived\n";
    file << "[1024] room \"909\": employee \"Charlie\" arrived\n";
    file << "[1025] room \"707\": guest \"Fiona\" departed\n";
    file << "[1026] room \"505\": guest \"Jack\" arrived\n";
    file << "[1027] room \"303\": guest \"Ivan\" departed\n";
    file << "[1028] room \"404\": employee \"Karen\" arrived\n";
    file << "[1029] room \"808\": guest \"Hank\" departed\n";
    file << "[1030] room \"505\": guest \"Jack\" departed\n";


    //Close File
    file.close();
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


int main(){
    cout << "----- TESTS FOR LOG READ -----" << endl << endl;
    generateSampleLogFile("log.txt");

    

    cout << endl <<"----- All tests for log read passed -----" << endl;
    return 0;
}