#include "stats.h"

#include <iomanip>
#include <sstream>

// One line of the table, padded into columns 6, 12, and 9 characters wide.
void print_row(std::ostream& out, const std::string& name, const std::string& turnaround,
               const std::string& waiting, const std::string& response) {
    out << std::left << std::setw(6) << name << std::setw(12) << turnaround
        << std::setw(9) << waiting << response << '\n';
}

std::string two_decimals(double value) {
    std::ostringstream text;
    text << std::fixed << std::setprecision(2) << value;
    return text.str();
}

std::vector<task_stats> compute_stats(const std::vector<task>& tasks) {
    std::vector<task_stats> stats;
    for (const task& current : tasks) {
        task_stats row;
        row.name = current.name;
        row.turnaround = current.completion;
        row.waiting = current.completion - current.burst;
        row.response = current.first_run;
        stats.push_back(row);
    }
    return stats;
}

void print_stats(const std::vector<task_stats>& stats, std::ostream& out) {
    out << "\nScheduling Statistics\n";
    print_row(out, "Task", "Turnaround", "Waiting", "Response");

    int total_turnaround = 0;
    int total_waiting = 0;
    int total_response = 0;
    for (const task_stats& row : stats) {
        print_row(out, row.name, std::to_string(row.turnaround), std::to_string(row.waiting),
                  std::to_string(row.response));
        total_turnaround += row.turnaround;
        total_waiting += row.waiting;
        total_response += row.response;
    }

    if (stats.empty()) {
        return;
    }
    const double count = static_cast<double>(stats.size());
    print_row(out, "Avg", two_decimals(total_turnaround / count), two_decimals(total_waiting / count),
              two_decimals(total_response / count));
}
