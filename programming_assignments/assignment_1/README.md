# Assignment 1: `ossh`

This is a small c shell that reads a command line or batch file and seperates the command and runs each in it's own child process.

## Build, run, and test

I set up a makefile for easy compilation of tests, which I used to verify the code, and easy running, since there are multiple files that hte logic is spread out between

| Command | What it does |
| --- | --- |
| `make` | Build the shell as `build/ossh` |
| `make run` | Build if needed, then start the shell |
| `make test` | Build and run all tests (`make tests` and `make run-tests` also work) |
| `make clean` | Remove generated programs from `build/` |
| `make help` | Show these commands in the terminal |

## Running the tests

From this assignment directory, run:

```sh
make run-tests
```

This builds the test programs if needed, then runs the shell and string helper tests. Each program prints its results in the terminal. If a test fails, the command exits with an error.

`make test` and `make tests` run the same tests. Use `make run-tests` with a hyphen; `make run tests` starts the interactive shell first.
