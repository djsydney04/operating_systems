#include "gantt.h"

void print_gantt(const std::vector<gantt_segment>& segments, std::ostream& out) {
    out << "CPU Scheduling Gantt Chart\n";
    if (segments.empty()) {
        out << "(no tasks ran)\n";
        return;
    }

    std::string bars;
    std::string times;
    int total = 0;
    for (const gantt_segment& segment : segments) {
        const std::string cell = "| " + segment.name + " ";
        const std::string start = std::to_string(segment.start);
        bars += cell;
        times += start;
        // Pad so the next time lines up under the next bar, with at least one space.
        times += std::string(cell.size() > start.size() ? cell.size() - start.size() : 1, ' ');
        total += segment.end - segment.start;
    }
    bars += "|";
    times += std::to_string(segments.back().end);

    out << bars << '\n' << times << "\n\n";
    out << "Total CPU Execution Time: " << total << " ms\n";
}
