#include "queues.h"
#include "test_helpers.h"

int main() {
    // Two tasks per queue for Q1-Q3, listed out of order so sorting shows.
    std::vector<task> tasks = {
        make_task("A", 2, 20, 1, 0), make_task("B", 9, 10, 1, 1),   // Q1: priorities 2, 9
        make_task("C", 5, 30, 2, 2), make_task("D", 5, 15, 2, 3),   // Q2: bursts 30, 15
        make_task("E", 5, 20, 3, 4), make_task("F", 5, 25, 3, 5),   // Q3
    };
    ready_queues queues = build_ready_queues(tasks);
    check(queues[0] == std::deque<int>{1, 0}, "Q1 is sorted by priority");
    check(queues[1] == std::deque<int>{3, 2}, "Q2 is sorted by burst");
    check(queues[2] == std::deque<int>{4, 5}, "Q3 keeps input order");

    check(first_ready_queue(queues) == 1, "Q1 is picked first");
    check(take_front(queues, 1) == 1 && queues[0] == std::deque<int>{0}, "take_front removes the front task");

    requeue_round_robin(queues, tasks, take_front(queues, 3));
    check(queues[2] == std::deque<int>{5, 4}, "Requeued task goes to the back of Q3");

    ready_queues empty = build_ready_queues({});
    check(first_ready_queue(empty) == 0, "No queue when all are empty");

    return finish();
}
