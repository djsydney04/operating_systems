#pragma once

#include "gantt.h"
#include "task.h"

#include <vector>

// Runs all tasks to completion and returns the Gantt chart segments.
std::vector<gantt_segment> run_scheduler(std::vector<task>& tasks);
