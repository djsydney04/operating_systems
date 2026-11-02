#include "scheduler.h"

#include "algorithms.h"
#include "queues.h"

std::vector<gantt_segment> run_scheduler(std::vector<task>& tasks) {
    ready_queues queues = build_ready_queues(tasks);
    std::vector<gantt_segment> segments;

    int clock = 0;
    int running = -1;       // index of the task on the CPU, -1 when the CPU is free
    int slice = 0;          // ticks the running task gets this turn
    int slice_used = 0;
    int slice_start = 0;

    while (running != -1 || first_ready_queue(queues) != 0) {
        if (running == -1) {
            running = take_front(queues, first_ready_queue(queues));
            task& picked = tasks[static_cast<std::size_t>(running)];
            if (picked.first_run == -1) {
                picked.first_run = clock;
            }
            slice = time_slice(picked);
            slice_used = 0;
            slice_start = clock;
        }

        task& current = tasks[static_cast<std::size_t>(running)];
        --current.remaining;
        ++clock;
        ++slice_used;

        if (current.remaining <= 0 || slice_used >= slice) {
            // A round-robin task picked again right away stays one continuous segment.
            if (!segments.empty() && segments.back().name == current.name &&
                segments.back().end == slice_start) {
                segments.back().end = clock;
            } else {
                segments.push_back({current.name, slice_start, clock});
            }

            if (current.remaining <= 0) {
                current.completion = clock;
            } else {
                requeue_round_robin(queues, tasks, running);
            }
            running = -1;
        }
    }
    return segments;
}
