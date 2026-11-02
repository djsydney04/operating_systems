# Assignment 2: Multilevel Queue CPU Scheduler
Dylan Mitic

## Design Overview

Below is a breakout of the file structure I used to build the scheduler. 

As you would expect, main is my entry point that reads the input file, runs the scheduler, and prints the results. 

File structure:

assignment_2/
├── makefile              # build, run, and test targets. All of the compiler flags, build, run, and test commands live here
├── README.md // You are here :)
├── .gitignore // track all of my work in github so this just keeps executables out of my git history 
├── src/
│   ├── main.cpp          # This is the entry point for the program. It reads the file, runs the scheduler, prints the chart and stats
│   ├── task.h            # This is where I defined the task struct, queue numbers, and the 10 ms time quantum
│   ├── queues.h/.cpp     # This builds the four ready queues and adds each task to its queue, then picks the next task and requeues round robin
│   ├── algorithms.h/.cpp # This houses the priority and SJF sorting, and defines the rr time slice
│   ├── scheduler.h/.cpp  # This is the clock-driven simulation loop
│   ├── gantt.h/.cpp      # This prints the Gantt chart
│   └── stats.h/.cpp      # This computes and prints the statistics
├── utils/
│   ├── task_reader.h/.cpp # This reads and parses the input file
│   └── utils.h            # Houses the inline trim helper done a bit more elegantly than in assignment 1
├── tests/
│   ├── fixtures/         # input files (see test fixtures below)
│   └── unit/             # I added a narrow test program for each part of the code so the core behavior stays correct while I make changes.
│       ├── test_parse_task_line.cpp # reading one input line
│       ├── test_algorithms.cpp      # priority and SJF ordering, time slice
│       ├── test_ready_queues.cpp    # building, picking from, and requeuing the queues
│       ├── test_scheduler.cpp       # full run of the assignment example
│       ├── test_stats.cpp           # statistics and averages
│       └── test_helpers.h           # shared check and setup helpers
└── output/               # program output for each input file, written by make run-all
```

### Queue data structures

In terms of data structures, I used four key ones:

1. A task struct that holds everything about one task: name, priority, burst, remaining time, queue number, input position, and the times it first ran and finished.
2. A std::vector<task> that stores every task once, in input order.
3. A std::array of four std::deque<int>, one per ready queue, that holds the order tasks will run in. Each deque holds indexes into the task vector rather than copies, so there is only one copy of each task to update. I used a deque because the scheduler removes tasks from the front and round robin adds them back at the end, and a deque does both quickly.
4. A std::vector<gantt_segment>, where each segment is one task's name with its start and end times, used to print the Gantt chart.

| Queue | Type | Algorithm | How its deque is ordered |
| --- | --- | --- | --- |
| 1 | Real-time | Priority | Sorted once at the start, highest priority number first |
| 2 | System | Shortest Job First | Sorted once at the start, shortest burst first |
| 3 | Interactive | Round Robin, 10 ms quantum | Input order; unfinished tasks go to the back |
| 4 | Batch | First Come First Served | Input order |

Ties in queues 1 and 2 go to the task that appeared first in the input file. Because every task arrives at time 0, queues 1 and 2 only need to be sorted once, before the simulation starts.

### How the scheduler selects tasks

The simulation runs in a loop where each pass is 1 ms of CPU time:

1. If the CPU is free (the running task index is -1), the scheduler checks queues 1, 2, 3, and 4 in that order and takes the task at the front of the first one that isn't empty. A lower-numbered queue always goes before a higher one.

2. It decides how long that task may run this turn. A round-robin task gets at most 10 ms; a task from any other queue runs until it finishes.

3. Each tick, the task loses 1 ms of remaining time and the clock moves forward 1 ms.

4. When the task finishes or uses up its turn, the scheduler records a Gantt chart segment. A finished task gets its completion time and unfinished round-robin task goes to the back of queue 3. The CPU is then free again and the next pass will pick up a new task.

The stop condition on the loop is when the CPU is free and all queues are empty.

### Statistics

All of the stats are computed from the definitions we went over in class. However, it should be noted that since all of the tasks arrive at time 0, turnaround time is just completion time. 

## Build & run Instructions

There are quite a few files here (I prefer to work in smaller files) so I used a makefile to have compilation be easy. 

To compile and run:

```sh
cd assignment_2
make run # builds and runs the scheduler on tests/fixtures
```

When you are finished use `make clean` to clear the executables. 

All of the outputs will be in a `/output` directory in the root. 

To compile without using make:

```sh
g++ -Isrc -Iutils -std=c++17 -Wall -Wextra -pedantic src/*.cpp utils/*.cpp -o scheduler
./scheduler tests/fixtures/input.txt
```

## Test commands

I also added some pretty narrow unit tests to test the functionality of the files that I had written. If you are interested in running those run `make test` which will compile and run those tests


## Test fixtures

Input files are in `tests/fixtures/`, and `make run-all` saves their output in `output/` under the same name.

- `input.txt` was given with the assignment. Most of the code was built against this test fixture.

I also created two additonal text fixtures to test contracts outline in the assignment spec: 

- `ties.txt` tests how equal priorities in queue 1 and equal bursts in queue 2 resolve. Earlier line must win each tie. 
- `round_robin.txt` tests rr with burst that aren't mutiples of 10 (so they get messy)

## Collaboration

just me 

## Known bugs or problems

None. Input handeling assumes a strict input which could cause issues if the input is malformed. Otherwise, none. 