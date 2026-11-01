#pragma once

// The four ready queues, one for each queue number in the input file.
// Each task goes into the queue that matches its queue number and never moves to another.
// The scheduler always serves the lowest-numbered queue that still has tasks, and an
// unfinished round-robin task goes back to the end of queue 3.
