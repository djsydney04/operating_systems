#pragma once

#include "task.h"

#include <deque>
#include <vector>

// Sort queue 1 by highest priority and queue 2 by shortest burst.
// Ties keep the earlier input line.
void sort_real_time_queue(std::deque<int>& indexes, const std::vector<task>& tasks);
void sort_system_queue(std::deque<int>& indexes, const std::vector<task>& tasks);

// Max ms a task runs before the scheduler picks again (10 for round robin).
int time_slice(const task& current);
