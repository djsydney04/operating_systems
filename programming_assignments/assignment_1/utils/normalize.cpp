#include "normalize.h"
#include <cctype>

std::string normalize(std::string command) {
    for (char& ch : command) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return command;
}