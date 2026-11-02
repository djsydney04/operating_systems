#include "task_reader.h"
#include "utils.h"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool parse_task_line(const std::string& line, int input_order, task& task) {
    std::istringstream parser(line);
    std::string priority_s, burst_s, queue_s;

    if (!std::getline(parser, task.name, ',')) return false;
    if (!std::getline(parser, priority_s, ',')) return false;
    if (!std::getline(parser, burst_s, ',')) return false;
    if (!std::getline(parser, queue_s, ',')) return false;

    task.name = trim(task.name);
    // stoi throws if a field doesn't start with a number.
    try {
        task.priority = std::stoi(priority_s);
        task.burst = std::stoi(burst_s);
        task.queue = std::stoi(queue_s);
    } catch (const std::exception&) {
        return false;
    }
    task.remaining = task.burst;
    task.input_order = input_order;
    return true;
}

// Reads the input file and returns a vector of tasks 
std::vector<task> read_tasks(const std::string& filename) {
    std::ifstream file(filename.c_str());

    if (!file) {
        throw std::runtime_error("File not found: " + filename);
    }
    std::vector<task> tasks;
    std::string line;

    while (std::getline(file, line)) {
        if (trim(line).empty()) {
            continue;
        }
        task current_task;
        if (!parse_task_line(line, static_cast<int>(tasks.size()), current_task)) {
            throw std::runtime_error("Invalid task line: " + line);
        }
        tasks.push_back(current_task);
    }
    return tasks;
}
