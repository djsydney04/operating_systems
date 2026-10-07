#include "shell.h"
#include "batch.h"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cerr << "usage: ossh [batch_file]\n";
        return 1;
    }

    // With no batch-file argument, read commands interactively.
    if (argc == 1) {
        std::string command;
        // Stop at the end of input or when a command requests quit.
        while (true) {
            std::cout << "ossh> " << std::flush;
            if (!std::getline(std::cin, command)) {
                break;
            }
            if (execute_line(command)) {
                break;
            }
        }
        return 0;
    }

    std::ifstream batch_file(argv[1]);
    if (!batch_file) {
        std::cerr << "cannot open batch file: " << argv[1] << '\n';
        return 1;
    }
    batch_file.close();

    // Echo each batch line, then run it. No prompt in batch mode.
    std::vector<std::string> commands = read_batch_file(argv[1]);
    execute_commands(commands);
    return 0;
}
