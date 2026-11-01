#pragma once

#include <string>

//constants for the scheduler 
const int queue_count = 4;
const int time_quantum = 10;    // round-robin slice in ms
const int min_priority = 1;
const int max_priority = 10;

// Queue numbers from the input file. A lower number is a higher-priority queue.
enum queue_type {
    real_time_queue = 1,    // Priority
    system_queue = 2,       // SJF
    interactive_queue = 3,  // Round robin
    batch_queue = 4         // FCFS
};

// Data strucuter for a task to be scheuled. 
struct task {
    std::string name;
    int priority = 0;
    int burst = 0;          // original CPU burst in ms
    int remaining = 0;      // ms left to run
    int queue = 0;          // 1-4, see queue_type
    int input_order = 0;    // 0-based line position, used to break ties
    int first_run = -1;     // clock time of first execution, -1 until it runs
    int completion = -1;    // clock time it finished, -1 until done
};
