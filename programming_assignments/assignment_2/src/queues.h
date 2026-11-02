#pragma once

#include "task.h"

#include <array>
#include <deque>
#include <vector>

// One deque of task indexes per queue; queue N is stored at [N - 1]
using ready_queues = std::array<std::deque<int>, queue_count>;

// Builds the ready queues for the given tasks.
ready_queues build_ready_queues(const std::vector<task>& tasks);

// Finds the first non-empty queue.
int first_ready_queue(ready_queues& queues);

// Takes the front task from the given queue.
int take_front(ready_queues& queues, int queue_number);

// Round robin: a task whose time slice ran out goes to the back of the queu
void requeue_round_robin(ready_queues& queues, const std::vector<task>& tasks, int task_index);
