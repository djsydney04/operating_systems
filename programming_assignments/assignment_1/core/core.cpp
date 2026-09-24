#include "core.h"
#include "../utils/normalize.h"
#include <sstream>
#include <string>

void execute(std::string command) {
    if (std::string(normalize(command)) == "quit") {
        return;
    }
    std::stringstream stream(command);
    std::string piece;
    while (std::getline(stream, piece, ';')) {
        
    }
}
