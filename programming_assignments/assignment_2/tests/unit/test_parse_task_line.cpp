#include "task_reader.h"
#include "test_helpers.h"

int main() {
    task t;
    check(parse_task_line("T3, 3, 25, 3", 2, t), "Accepts a full line");
    check(t.name == "T3" && t.priority == 3 && t.burst == 25 && t.queue == 3, "Reads every field");
    check(t.remaining == 25 && t.input_order == 2, "Sets remaining and input order");

    task bad;
    check(!parse_task_line("T2, 2, 25", 0, bad), "Rejects a missing field");
    check(!parse_task_line("T2, abc, 25, 1", 0, bad), "Rejects a field that isn't a number");

    return finish();
}
