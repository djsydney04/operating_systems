#include "shell.h"
#include "batch.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // With no batch-file argument, read commands interactively.
    if (argc == 1) {
        // Clear the terminal, then move the cursor to the top-left.
        std::cout << "\033[2J\033[H" << std::flush;
        std::string command;
        // Stop at the end of input (Ctrl-D) or when a command requests quit.
        while (true) {
            std::cout << "ossh> " << std::flush;
            if (!std::getline(std::cin, command)) {
                break;
            }
            if (execute_line(command)) {
                break;
            }
        }
    } else if (argc == 2) {
        std::vector<std::string> commands = read_batch_file(argv[1]);
        execute_commands(commands);
    }
    return 0;
}
