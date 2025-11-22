#include "common.hpp"
#include "logappend.hpp"
#include <fstream>

using namespace std;

/*
logappend -T <timestamp> -K <token> (-E <employee-name> | -G <guest-name>) (-A | -L) [-R <room-id>] <log>
*/

// function that takes the map of args and handles calling logwrite to append
// returns: error code 0 = success, 255 = error
int handleArgs(const std::map<std::string, std::string> &args){
    // -E and -G flags cannot exist simulteanously, but  one needs to exist
        if(((args.find("-E") != args.end()) && (args.find("-G") != args.end())) || ((args.find("-E") == args.end()) && (args.find("-G") == args.end()))){
            cout << "invalid" << endl;
            return 255;
        }
        
        // -A and -L flags are same thing as -E and -G condition
        if(((args.find("-A") != args.end()) && (args.find("-L") != args.end())) || ((args.find("-A") == args.end()) && (args.find("-L") == args.end()))){
            cout << "invalid" << endl;
            return 255;
        }

        // timestamp must be there
        // TODO: check if timestamp is greater than that of most recent entry (in specification requirements)
        if(args.find("-T") == args.end()){
            cout << "invalid" << endl;
            return 255;
        }

        // roomId is optional
        string roomId = "";
        if(args.find("-R") != args.end()){
            roomId = args.at("-R");
        }

        // targetName is the name of guest/employee
        bool isEmployee = args.find("-E") != args.end();
        string targetName = isEmployee ? args.at("-E") : args.at("-G");

        string fileName = args.at("log");
        string timestamp = args.at("-T");
        bool isArrival = args.find("-A") != args.end();

        // TODO: handling for when there is no roomId
        // TODO: logWrite change to accept either guest or employee name 
        int returnCode = logWrite(fileName, targetName, isEmployee, stoi(roomId), isArrival, stoi(timestamp));
        
        // error handling
        if(returnCode == 255){
            cout << "invalid" << endl;
            return returnCode;
        }

        return 0;
}

int main(int argc, char *argv[]){
    auto args = parseArguments(argc, argv);

    // Autheticate Token
    if (!validateToken(args["-K"])) {
        std::cout << "Authentication Failed" << std::endl;
        return -1;
    }

    // Whether we are in batch file mode or not
    if(args.find("-B") == args.end()){
        return handleArgs(args);
    }
    // batch file mode
    else{
        string batchFileName = args.at("-B");

        ifstream batchFile(batchFileName);
        if(!batchFile.is_open()){
            cout << "invalid" << endl;
            return 255;
        }

        string line;
        while(getline(batchFile, line)){
            auto res = splitString(line, ' ');

            // NOTE: parseArguments expects the argc and argv that main creates, so we need to recreate that
            // from the split string
            int newArgc = res.size() + 1;
            
            const char **newArgv = new const char*[newArgc];
            newArgv[0] = "nothing"; // should be filename but doesnt exist here
            for(int i = 1; i < newArgc; i++){
                newArgv[i] = res.at(i-1).c_str();
            }

            // I had to remove constness because the c_str function from string returns a const char* and parseArgs
            // expects non-const
            args = parseArguments(newArgc, const_cast<char**>(newArgv));
            int errorCode = handleArgs(args);
            if(errorCode == 255) return errorCode;
        }
    }

    return 0;
}