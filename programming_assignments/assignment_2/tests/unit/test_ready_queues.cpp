#include "queues.h"
#include "task_reader.h"

#include <iostream>
#include <string>
#include <vector>

static int failures = 0;

void check(bool pass, const std::string& test_name) {
    if (pass) {
        std::cout << "✓ " << test_name << '\n';
    } else {
        std::cout << "✗ " << test_name << '\n';
        ++failures;
    }
}

std::string get_front_name(const ready_queues& queues, const std::vector<task>& tasks, int q) {
    return tasks[front_task(queues, q)].name;
}

int main() {
    // Test 1: Sample file queue ordering
    std::vector<task> sample = read_tasks("tests/fixtures/input.txt");
    ready_queues queues = build_ready_queues(sample);
    
    check(get_front_name(queues, sample, 1) == "T5", "Priority queue: T5 (priority 10) is first");
    check(get_front_name(queues, sample, 2) == "T2", "SJF queue: T2 (burst 25) is first");
    check(get_front_name(queues, sample, 3) == "T3", "Round-robin queue: T3 is first (input order)");
    check(get_front_name(queues, sample, 4) == "T4", "FCFS queue: T4 is first (input order)");
    check(first_ready_queue(queues) == 1, "Queue 1 has highest priority");

    // Test 2: Take and return operations
    take_front(queues, 1);  // Remove T5
    check(get_front_name(queues, sample, 1) == "T1", "After removing T5, T1 is next");
    
    int t3_index = take_front(queues, 3);  // Remove T3 from queue 3
    return_to_queue(queues, sample, t3_index);  // Put it back
    check(get_front_name(queues, sample, 3) == "T7", "After T3 returns to back, T7 is now front");

    // Test 3: All tests passed
    std::cout << "\n";
    if (failures == 0) {
        std::cout << "All tests passed!\n";
    } else {
        std::cout << failures << " test(s) failed\n";
    }
    return failures;
}
