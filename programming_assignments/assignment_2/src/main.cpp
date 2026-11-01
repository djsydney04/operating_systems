#include "task_reader.h"

#include <exception>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: scheduler <task_file>\n";
        return 1;
    }

    try {
        std::vector<task> tasks = read_tasks(argv[1]);
        // Next: run the scheduler on tasks, then print the Gantt chart and statistics.
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
