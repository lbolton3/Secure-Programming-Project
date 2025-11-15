#include "common.hpp"
#include "logappend.hpp"

using namespace std;

/*
logappend -T <timestamp> -K <token> (-E <employee-name> | -G <guest-name>) (-A | -L) [-R <room-id>] <log>
*/

int main(int argc, char *argv[]){
    auto args = parseArguments(argc, argv);

    // debug
    // for(auto i = args.begin(); i != args.end(); i++){
    //     cout << (*i).first << " " << (*i).second << std::endl;
    // }

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