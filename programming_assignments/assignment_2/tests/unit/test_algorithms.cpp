#include "algorithms.h"
#include "test_helpers.h"

int main() {
    // Priorities 2, 8, 8: the 8s go first, earlier line wins the tie.
    std::vector<task> tasks = {make_task("A", 2, 10, 1, 0), make_task("B", 8, 10, 1, 1), make_task("C", 8, 10, 1, 2)};
    std::deque<int> queue = {2, 0, 1};
    sort_real_time_queue(queue, tasks);
    check(queue == std::deque<int>{1, 2, 0}, "Priority: highest first, ties by input order");

    // Bursts 30, 15, 15: the 15s go first, earlier line wins the tie.
    tasks = {make_task("A", 9, 30, 2, 0), make_task("B", 1, 15, 2, 1), make_task("C", 5, 15, 2, 2)};
    queue = {2, 0, 1};
    sort_system_queue(queue, tasks);
    check(queue == std::deque<int>{1, 2, 0}, "SJF: shortest first, ties by input order");

    check(time_slice(make_task("A", 1, 25, 3, 0)) == 10, "Round robin gets at most 10 ms");
    check(time_slice(make_task("A", 1, 5, 3, 0)) == 5, "Round robin with 5 ms left gets 5");
    check(time_slice(make_task("A", 1, 30, 2, 0)) == 30, "Other queues run to completion");

    return finish();
}
