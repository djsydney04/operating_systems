#include <iostream>
#include <string>
#include "utils/normalize.h"

int main(int argc, char* argv[]) {
    // If the user does not provide a batch file, run the shell in interactive mode 
    if (argc == 1) {
        // Clear the terminal, then move the cursor to the top-left. Better UX :)
        std::cout << "\033[2J\033[H" << std::flush;
        std::string command;
        // Read commands from stdin until the user exits the shell
        while (true) {
            std::cout << "ossh> " << std::flush;
            std::getline(std::cin, command);
            // Normalize the command so "QUIT" matches "quit"
            if (std::string(normalize(command)) == "quit") {
                break;
            }
            // Execute the command
            if (!command.empty()) {
                std::cout << command << std::endl;
            }
        }
    } else if (argc == 2) {
        std::string command = argv[1];
        std::cout << command << std::endl;
    }

    return 0;

}