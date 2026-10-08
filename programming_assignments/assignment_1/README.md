# Assignment 1: ossh
Dykan Mitic 

This is a small C++ shell that reads a command line or a batch file, separates the commands, and runs each one in its own child process.

## Design Overview

Below is a breakout of the file strucutre that I used to build the shell. Main houses the entry point and interactive vs batch functionality routing. Shell.cpp houses the shell parsing and command execution. batch.cpp houses the file read in and batch execution. 

File structure:

```text
assignment_1/
├── makefile              # build, run, and test targets. `make` writes ./ossh here.
├── README.md
├── .gitignore          
├── src/
│   ├── main.cpp          # interactive loop and batch-file entry
│   ├── shell.h           # command split and execute declarations
│   ├── shell.cpp
│   ├── batch.h           # batch-file read and execute declarations
│   ├── batch.cpp
│   ├── string_utils.h    # trim and lowercase helpers that are used to normalize cli inputs
│   └── string_utils.cpp
└── tests/ # I added a pretty narrow test suite that checks core functionality. I started manually, but wanted to make sure that all of these contracts remained correct while I was making code changes, so added them as repeatable tests. 
    ├── test_shell.cpp # Shell tests 
    ├── test_batch.cpp # Batching tests
    └── test_string_utils.cpp # String helpers tests 
```

make writes the ossh executable in this directory, so ./ossh starts the shell. Test programs go in build. Neither is checked in. 

## Build & run Instructions:
To compile and run 

```sh 
cd assignment_1 
make run # builds and runs the ossh program
./ossh #enters the shell
```

To compile without using make:

```sh
g++ -Isrc -std=c++17 -Wall -Wextra -pedantic src/main.cpp src/shell.cpp src/batch.cpp src/string_utils.cpp -o ossh
./ossh
```

## Build, run, and test commands

I set up a makefile for easy compilation across the four files in SRC + the test files. 

| Command | What it does |
| --- | --- |
| `make` | Build the shell as `./ossh` |
| `make run` | Build if needed, then start the shell |
| `make test` | Build and run all tests (`make tests` and `make run-tests` also work) |
| `make clean` | Remove `ossh` and the test programs from this folder |

## Known bugs or problems

- I discussed this with you in class, but cd seems like it can't be executed by the child process since it changes the directory for the parent process, to handle this, and make the shell more usable, I added an exception in shell.cpp.
