#include "queues.h"

#include "algorithms.h"

#include <stdexcept>

// builds the ready queues for the given tasks
ready_queues build_ready_queues(const std::vector<task>& tasks) {
    ready_queues queues;

    // adds each task to the appropriate queue
    for (int index = 0; index < static_cast<int>(tasks.size()); ++index) {
        const task& current = tasks[static_cast<std::size_t>(index)];
        // checks for a bad queue number
        if (current.queue < 1 || current.queue > queue_count) {
            throw std::runtime_error("task " + current.name + " has a queue outside 1-4");
        }
        // adds the task to the appropriate queue
        queues[current.queue - 1].push_back(index);
    }

    sort_real_time_queue(queues[real_time_queue - 1], tasks);
    sort_system_queue(queues[system_queue - 1], tasks);
    // Round robin (queue 3) and FCFS (queue 4) start in input order, so they are not sorted.

    return queues;
}

int first_ready_queue(ready_queues& queues) {
    for (int queue_number = 1; queue_number <= queue_count; ++queue_number) {
        if (!queues[queue_number - 1].empty()) {
            return queue_number;
        }
    }
    return 0;
}

int take_front(ready_queues& queues, int queue_number) {
    std::deque<int>& queue = queues[queue_number - 1];
    if (queue.empty()) {
        throw std::runtime_error("ready queue is empty");
    }
    const int task_index = queue.front();
    queue.pop_front();
    return task_index;
}

// Round robin: a task whose time slice ran out goes to the back of queue 3.
void requeue_round_robin(ready_queues& queues, const std::vector<task>& tasks, int task_index) {
    if (task_index < 0 || task_index >= static_cast<int>(tasks.size())) {
        throw std::runtime_error("task index out of range");
    }
    if (tasks[static_cast<std::size_t>(task_index)].queue != interactive_queue) {
        throw std::runtime_error("only round-robin tasks are requeued");
    }
    queues[interactive_queue - 1].push_back(task_index);
}
