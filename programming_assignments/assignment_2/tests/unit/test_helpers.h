#pragma once

#include "task.h"

#include <iostream>
#include <string>

inline int failures = 0;

inline void check(bool pass, const std::string& name) {
    std::cout << (pass ? "passed " : "failed ") << name << '\n';
    if (!pass) ++failures;
}

// Prints the summary; the return value is the program's exit code.
inline int finish() {
    std::cout << (failures == 0 ? "All tests passed!\n\n" : "Some tests failed\n\n");
    return failures;
}

inline task make_task(const std::string& name, int priority, int burst, int queue, int input_order) {
    task t;
    t.name = name;
    t.priority = priority;
    t.burst = burst;
    t.remaining = burst;
    t.queue = queue;
    t.input_order = input_order;
    return t;
}
