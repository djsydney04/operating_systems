#pragma once

#include <string>
#include <vector>
#include "task.h"

bool parse_task_line(const std::string& line, int input_order, task& parsed);

std::vector<task> read_tasks(const std::string& filename);
