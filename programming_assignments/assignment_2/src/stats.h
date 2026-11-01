#pragma once

// Every task arrives at time 0, so for each task: turnaround is its completion time,
// waiting is turnaround minus its burst, and response is its first run time.
// Prints one row per task in input order, then the average of each column.
