#include <iostream>

namespace cli {
    void read_file(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }

}