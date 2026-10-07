#pragma once

#include <string>
#include <vector>

// Separate a line at semicolons, then trim each command.
std::vector<std::string> split_commands(std::string line);

// Separate one command into whitespace-delimited words.
std::vector<std::string> split_words(std::string command);

// Run commands in order. Returns true only when quit requests a shell exit.
bool execute_line(std::string line);
