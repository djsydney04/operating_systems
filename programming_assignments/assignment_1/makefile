# Makefile for the assignment 1 shell
# This compiles the shell, runs the tests, and runs the shell

# Set the compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
CPPFLAGS += -Isrc

# Set the output file and source files
OSSH = build/ossh
SOURCES = src/main.cpp src/shell.cpp src/string_utils.cpp
HEADERS = src/shell.h src/string_utils.h
TEST_BINARIES = build/test_shell build/test_string_utils

# Set the phony targets
.PHONY: all test tests run-tests run clean help

# Keep building, testing, and running as separate, explicit steps.
all: $(OSSH)

$(OSSH): $(SOURCES) $(HEADERS) | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) -o $@

build/test_shell: tests/test_shell.cpp src/shell.cpp src/string_utils.cpp $(HEADERS) | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/test_shell.cpp src/shell.cpp src/string_utils.cpp -o $@

build/test_string_utils: tests/test_string_utils.cpp src/string_utils.cpp src/string_utils.h | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/test_string_utils.cpp src/string_utils.cpp -o $@

build:
	mkdir -p build

test: $(TEST_BINARIES)
	./build/test_shell
	./build/test_string_utils

tests run-tests: test

run: $(OSSH)
	./$(OSSH)

clean:
	rm -f $(OSSH) $(TEST_BINARIES)

help:
	@echo "make        Build build/ossh"
	@echo "make run    Build and start the shell"
	@echo "make test   Build and run all tests"
	@echo "make run-tests  Alias for make test (make tests also works)"
	@echo "make clean  Remove generated programs"
