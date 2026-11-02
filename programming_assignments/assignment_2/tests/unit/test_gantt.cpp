#include "gantt.h"
#include "test_helpers.h"

#include <sstream>

int main() {
    // The schedule from the assignment's example.
    std::ostringstream out;
    print_gantt({{"T5", 0, 10},    {"T1", 10, 30},   {"T2", 30, 55},   {"T6", 55, 85},
                 {"T3", 85, 95},   {"T7", 95, 105},  {"T3", 105, 115}, {"T7", 115, 125},
                 {"T3", 125, 130}, {"T4", 130, 145}, {"T8", 145, 160}},
                out);
    check(out.str() ==
              "CPU Scheduling Gantt Chart\n"
              "| T5 | T1 | T2 | T6 | T3 | T7 | T3 | T7 | T3 | T4 | T8 |\n"
              "0    10   30   55   85   95   105  115  125  130  145  160\n"
              "\n"
              "Total CPU Execution Time: 160 ms\n",
          "Prints the assignment's example chart");

    return finish();
}
