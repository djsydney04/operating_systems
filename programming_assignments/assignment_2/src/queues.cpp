#include "queues.h"

#include "algorithms.h"

#include <algorithm>
#include <stdexcept>

namespace {

// returns the queue at the given queue number
std::deque<int>& queue_at(ready_queues& queues, int queue_number) {
    if (queue_number < 1 || queue_number > queue_count) {
        throw std::out_of_range("queue number out of range");
    }
    return queues.indexes[static_cast<std::size_t>(queue_number - 1)];
}

const std::deque<int>& queue_at(const ready_queues& queues, int queue_number) {
    if (queue_number < 1 || queue_number > queue_count) {
        throw std::out_of_range("queue number out of range");
    }
    return queues.indexes[static_cast<std::size_t>(queue_number - 1)];
}

// Highest priority number first. Equal priority keeps the earlier input line.
void sort_real_time_queue(std::deque<int>& indexes, const std::vector<task>& tasks) {
    std::sort(indexes.begin(), indexes.end(), [&](int left, int right) {
        return higher_priority_first(tasks[static_cast<std::size_t>(left)],
                                      tasks[static_cast<std::size_t>(right)]);
    });
}

// Shortest burst first. Equal bursts keep the earlier input line.
void sort_system_queue(std::deque<int>& indexes, const std::vector<task>& tasks) {
    std::sort(indexes.begin(), indexes.end(), [&](int left, int right) {
        return shorter_job_first(tasks[static_cast<std::size_t>(left)],
                                  tasks[static_cast<std::size_t>(right)]);
    });
}

}  // namespace

// builds the ready queues for the given tasks
ready_queues build_ready_queues(const std::vector<task>& tasks) {
    ready_queues queues;

    // adds each task to the appropriate queue
    for (int index = 0; index < static_cast<int>(tasks.size()); ++index) {
        const task& current = tasks[static_cast<std::size_t>(index)];
        // checks for a bad queue number
        if (current.queue < 1 || current.queue > queue_count) {
            throw std::invalid_argument("task " + current.name + " has a queue outside 1-4");
        }
        // adds the task to the appropriate queue
        queue_at(queues, current.queue).push_back(index);
    }

    sort_real_time_queue(queue_at(queues, real_time_queue), tasks);
    sort_system_queue(queue_at(queues, system_queue), tasks);

    return queues;
}

int first_ready_queue(const ready_queues& queues) {
    for (int queue_number = 1; queue_number <= queue_count; ++queue_number) {
        if (!queue_at(queues, queue_number).empty()) {
            return queue_number;
        }
    }
    return 0;
}

int front_task(const ready_queues& queues, int queue_number) {
    const std::deque<int>& queue = queue_at(queues, queue_number);
    if (queue.empty()) {
        throw std::logic_error("ready queue is empty");
    }
    return queue.front();
}

int take_front(ready_queues& queues, int queue_number) {
    std::deque<int>& queue = queue_at(queues, queue_number);
    if (queue.empty()) {
        throw std::logic_error("ready queue is empty");
    }
    const int task_index = queue.front();
    queue.pop_front();
    return task_index;
}

void return_to_queue(ready_queues& queues, const std::vector<task>& tasks, int task_index) {
    if (task_index < 0 || task_index >= static_cast<int>(tasks.size())) {
        throw std::out_of_range("task index out of range");
    }
    const task& current = tasks[static_cast<std::size_t>(task_index)];
    queue_at(queues, current.queue).push_back(task_index);
}
