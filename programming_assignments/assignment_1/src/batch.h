#pragma once

#include <string>
#include <vector>
#include "shell.h"

std::vector<std::string> read_batch_file(std::string filename);
void execute_commands(std::vector<std::string> commands);