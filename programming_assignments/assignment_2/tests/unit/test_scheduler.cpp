#include "scheduler.h"
#include "task_reader.h"
#include "test_helpers.h"

int main() {
    // The assignment's example.
    std::vector<task> tasks = read_tasks("tests/fixtures/input.txt");
    std::vector<gantt_segment> segments = run_scheduler(tasks);

    std::string order;
    for (const gantt_segment& segment : segments) {
        order += segment.name + " ";
    }
    check(order == "T5 T1 T2 T6 T3 T7 T3 T7 T3 T4 T8 ", "Runs in the assignment's order");
    check(segments.back().end == 160, "Finishes at 160 ms");

    const task& t3 = tasks[2];
    check(t3.first_run == 85 && t3.completion == 130, "T3 first runs at 85 and finishes at 130");

    // A round-robin task alone in Q3 keeps the CPU: one bar, not three.
    std::vector<task> alone = {make_task("A", 1, 25, 3, 0)};
    check(run_scheduler(alone).size() == 1, "Lone round-robin task is one segment");

    return finish();
}
