#include "common.hpp"

std::map<std::string, std::string> parseArguments(int argc, char* argv[]) {
    std::map<std::string, std::string> arguments;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        // Check for the last argument (log file)
        if (i == argc - 1) {
            if (arg[0] != '-') {
                arguments["log"] = arg;
            }
        }

        // Process flags and their values
        if (arg[0] == '-') {
            std::string key = arg;
            std::string value;

            if ((i + 1) < argc && argv[i + 1][0] != '-') {
                value = argv[++i];
            } else {
                value = "true";  // Flag without value
            }

            arguments[key] = value;
        }
    }

    return arguments;
}

// see hpp
std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string piece;

    while (std::getline(ss, piece, delimiter)) {
        result.push_back(piece);
    }

    return result;
}

void printArgs(std::map<std::string, std::string> args) {
    for (auto i = args.begin(); i != args.end(); i++) {
        std::cout << i->first << " " << i->second << std::endl;
    }
}

std::string sha256(const std::string s) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(s.c_str()),
           s.size(),
           hash);

    std::ostringstream oss;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(hash[i]);
    }

    return oss.str();
}
