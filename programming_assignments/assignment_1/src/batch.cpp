#include <iostream>
#include <fstream>
#include <string>
#include "shell.h" 
#include "batch.h"

// Reads a batch file and returns a vector of commands
std::vector<std::string> read_batch_file(std::string filename) {
    std::vector<std::string> commands;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        commands.push_back(line);
    }
    return commands;
}

// Executes a vector of commands
void execute_commands(std::vector<std::string> commands) {
    for (const auto& command : commands) {
        execute_line(command);
        printf("Command executed: %s\n", command.c_str());
    }
}