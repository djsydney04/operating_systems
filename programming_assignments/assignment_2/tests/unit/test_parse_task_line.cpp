#include "task_reader.h"

#include <iostream>
#include <string>

static int failures = 0;

static void check(bool condition, const std::string& description) {
    if (!condition) {
        std::cout << "FAIL: " << description << '\n';
        ++failures;
    }
}

//unit test for parse_task_line function. Tests pretty narrow functionality that the function can parse the args from the file correctly.
int main() {
    task t;
    check(parse_task_line("T3, 3, 25, 3", 2, t), "accepts a full line");
    check(t.name == "T3", "name is trimmed and has no comma");
    check(t.priority == 3, "priority is read");
    check(t.burst == 25, "burst is read");
    check(t.remaining == 25, "remaining starts equal to burst");
    check(t.queue == 3, "queue is read");
    check(t.input_order == 2, "input_order is stored");

    task missing;
    check(!parse_task_line("T2, 2, 25", 0, missing), "rejects a line missing the queue");

    task empty;
    check(!parse_task_line("", 0, empty), "rejects an empty line");

    std::cout << (failures ? std::to_string(failures) + " check(s) failed\n"
                           : "All parse_task_line tests passed\n");
    return failures ? 1 : 0;
}
