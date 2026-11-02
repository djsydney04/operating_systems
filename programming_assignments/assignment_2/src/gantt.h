#pragma once

#include <ostream>
#include <string>
#include <vector>

// One continuous stretch of CPU time for a task, from start up to end (ms).
struct gantt_segment {
    std::string name;
    int start = 0;
    int end = 0;
};

// Prints the chart and the total CPU execution time.
void print_gantt(const std::vector<gantt_segment>& segments, std::ostream& out);
