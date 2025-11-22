#include "logread.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "----- This is logread -----" << std::endl;

    auto args = parseArguments(argc, argv);

    // Debug Argument Output
    // std::cout << std::endl;
    // std::cout << args.size() << " arguments found." << std::endl;
    // std::cout << "Parsed Arguments:" << std::endl;
    // for (const auto& pair : args) {
    //     std::cout << pair.first << ": " << pair.second << std::endl;
    // }

    // Autheticate Token
    if (!validateToken(args["-K"])) {
        std::cout << "Authentication Failed" << std::endl;
        return -1;
    }

    // Determine Operation
    if (args["-S"] != "") {
        printAttendants(args["log"], "employee");
        printAttendants(args["log"], "guest");
        printOccupiedRooms(args["log"]);

    } else if (args["-R"] != "") {
        // Employee Room History
        if (args["-E"] != "") {
            printRoomHistory(args["log"], args["-E"] != "" ? args["-E"] : args["-G"]);
        // Guest Room History
        } else if (args["-G"] != "") {
            printRoomHistory(args["log"], args["-G"]);
        }

    } else if (args["-T"] != "") {
        std::cout << "unimplemented" << std::endl;

    } else if (args["-I"] != "") {  
        std::cout << "unimplemented" << std::endl;

    } else {
        std::cout << "No valid operation specified." << std::endl;
    }

    return 0;
}