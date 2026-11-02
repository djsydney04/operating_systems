#include "algorithms.h"

#include <algorithm>

// Sorts the real-time queue by priority, then input order.
void sort_real_time_queue(std::deque<int>& indexes, const std::vector<task>& tasks) {
    std::sort(indexes.begin(), indexes.end(), [&](int left, int right) {
        if (tasks[left].priority != tasks[right].priority) {
            return tasks[left].priority > tasks[right].priority;
        }
        return tasks[left].input_order < tasks[right].input_order;
    });
}

// Sorts the system queue by burst time, then input order.
void sort_system_queue(std::deque<int>& indexes, const std::vector<task>& tasks) {
    std::sort(indexes.begin(), indexes.end(), [&](int left, int right) {
        if (tasks[left].burst != tasks[right].burst) {
            return tasks[left].burst < tasks[right].burst;
        }
        return tasks[left].input_order < tasks[right].input_order;
    });
}

// Returns the time slice for the given task in rr 
int time_slice(const task& current) {
    if (current.queue == interactive_queue) {
        return std::min(current.remaining, time_quantum);
    }
    return current.remaining;
}
