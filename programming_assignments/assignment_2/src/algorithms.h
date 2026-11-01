#pragma once

// The rules for picking the next task inside a single queue.
// Queue 1 (Priority) picks the highest priority number, and queue 2 (SJF) picks the
// shortest burst; both break ties by input order. Queue 3 (Round Robin) and
// queue 4 (FCFS) take whichever task is at the front of the queue.
