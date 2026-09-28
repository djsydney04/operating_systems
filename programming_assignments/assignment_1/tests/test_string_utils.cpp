#include "string_utils.h"

#include <iostream>
#include <string>

int main() {
    if (normalize("QuiT") != "quit") {
        std::cerr << "FAIL: normalize should convert uppercase letters" << std::endl;
        return 1;
    }
    if (trim("  cat file") != "cat file") {
        std::cerr << "FAIL: trim should remove leading spaces" << std::endl;
        return 1;
    }
    if (trim("ls -l  ") != "ls -l") {
        std::cerr << "FAIL: trim should remove trailing spaces" << std::endl;
        return 1;
    }
    if (trim("  quit  ") != "quit") {
        std::cerr << "FAIL: trim should remove spaces at both ends" << std::endl;
        return 1;
    }
    std::cout << "All string helper tests passed" << std::endl;
    return 0;
}
