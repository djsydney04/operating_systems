#include "algorithms.h"

// Higher priority number wins. Equal priority keeps the earlier input line.
bool higher_priority_first(const task& left, const task& right) {
    if (left.priority != right.priority) {
        return left.priority > right.priority;
    }
    return left.input_order < right.input_order;
}

// Shorter original burst wins. Equal bursts keep the earlier input line.
bool shorter_job_first(const task& left, const task& right) {
    if (left.burst != right.burst) {
        return left.burst < right.burst;
    }
    return left.input_order < right.input_order;
}
