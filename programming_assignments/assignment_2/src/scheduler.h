#pragma once

// The clock loop. Each tick is 1 ms: run the current task, lower its remaining time,
// and advance the clock. When the task finishes or uses up its 10 ms round-robin slice,
// pick the next task from the queues. Along the way, record each task's first run and
// completion time, plus each continuous stretch of CPU time for the Gantt chart.
