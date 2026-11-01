#pragma once

#include "task.h"

#include <array>
#include <deque>
#include <vector>


struct ready_queues {
    std::array<std::deque<int>, queue_count> indexes;
};


ready_queues build_ready_queues(const std::vector<task>& tasks);

int first_ready_queue(const ready_queues& queues);

int front_task(const ready_queues& queues, int queue_number);

int take_front(ready_queues& queues, int queue_number);

void return_to_queue(ready_queues& queues, const std::vector<task>& tasks, int task_index);
