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
    task.priority = std::stoi(trim(priority_s));
    task.burst = std::stoi(trim(burst_s));
    task.remaining = task.burst;
    task.queue = std::stoi(trim(queue_s));
    task.input_order = input_order;
    return true;
}

// Reads the input file and returns a vector of tasks 
std::vector<task> read_tasks(const std::string& filename) {
    std::ifstream file(filename.c_str());

    if (!file) {
        throw std::runtime_error("File not found: " + filename);
    }
    int input_order = 0;
    std::vector<task> tasks;
    std::string line;

    while (std::getline(file, line)) {
        task current_task;
        parse_task_line(line, input_order, current_task);
        tasks.push_back(current_task);
        ++input_order;
    }
    return tasks;
}
