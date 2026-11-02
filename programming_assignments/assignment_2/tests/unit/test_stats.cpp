#include "stats.h"
#include "test_helpers.h"

#include <sstream>

task finished(const std::string& name, int burst, int first_run, int completion) {
    task t = make_task(name, 1, burst, 1, 0);
    t.first_run = first_run;
    t.completion = completion;
    return t;
}

int main() {
    // T3 from the example: burst 25, first runs at 85, finishes at 130.
    task_stats t3 = compute_stats({finished("T3", 25, 85, 130)})[0];
    check(t3.turnaround == 130, "Turnaround is the completion time");
    check(t3.waiting == 105, "Waiting is turnaround minus burst");
    check(t3.response == 85, "Response is the first run time");

    // All eight tasks from the example.
    std::vector<task> tasks = {
        finished("T1", 20, 10, 30),  finished("T2", 25, 30, 55),   finished("T3", 25, 85, 130),
        finished("T4", 15, 130, 145), finished("T5", 10, 0, 10),   finished("T6", 30, 55, 85),
        finished("T7", 20, 95, 125), finished("T8", 15, 145, 160),
    };
    std::ostringstream out;
    print_stats(compute_stats(tasks), out);
    check(out.str().find("Avg   92.50       72.50    68.75\n") != std::string::npos, "Averages match the example");

    return finish();
}
