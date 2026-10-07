# Assignment 1: `ossh`

This is a small c++ shell that reads a command line or batch file and seperates the command and runs each in it's own child process.

## Design Overview

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

`make` writes the `ossh` executable in this directory, so `./ossh` starts the shell. Test programs still go in `build/`. Neither is checked in. 

## Build & run Instructions: 
To compile and run 

```sh 
cd assignment_1 
make run # builds and runs the ossh program
./ossh #enters the shell
```

## Build, run, and test commands

I set up a makefile for easy compilation of tests, which I used to verify the code, and easy running, since there are multiple files that hte logic is spread out between

| Command | What it does |
| --- | --- |
| `make` | Build the shell as `./ossh` |
| `make run` | Build if needed, then start the shell |
| `make test` | Build and run all tests (`make tests` and `make run-tests` also work) |
| `make clean` | Remove `ossh` and the test programs from this folder |
| `make help` | Show these commands in the terminal |
