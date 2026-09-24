#include <../utils/normalize.h>
#include <iostream>
#include <string>

int main() {
    std::string command = "QuiT";
    if (normalize(command) == "quit") {
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }
    return 0;
}