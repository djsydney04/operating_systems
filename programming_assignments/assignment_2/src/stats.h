#pragma once

#include "task.h"

#include <ostream>
#include <string>
#include <vector>

// Times in ms for one finished task. Every task arrives at time 0.
struct task_stats {
    std::string name;
    int turnaround = 0;     // completion
    int waiting = 0;        // turnaround - burst
    int response = 0;       // first run
};

// One entry per task, in input order. Call after run_scheduler.
std::vector<task_stats> compute_stats(const std::vector<task>& tasks);

// Prints one row per task and the average of each column.
void print_stats(const std::vector<task_stats>& stats, std::ostream& out);
