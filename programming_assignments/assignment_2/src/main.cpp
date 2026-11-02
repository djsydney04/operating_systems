#include "gantt.h"
#include "scheduler.h"
#include "stats.h"
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
        std::vector<gantt_segment> segments = run_scheduler(tasks);
        std::cout << '\n';
        print_gantt(segments, std::cout);
        print_stats(compute_stats(tasks), std::cout);
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
