# Makefile for the assignment 1 shell
# This compiles the shell, runs the tests, and runs the shell

# Set the compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
CPPFLAGS += -Isrc

# Compiled programs are written in this assignment directory (next to the makefile).
OSSH = ossh
TEST_SHELL = test_shell
TEST_STRING_UTILS = test_string_utils
TEST_BATCH = test_batch
SOURCES = src/main.cpp src/shell.cpp src/batch.cpp src/string_utils.cpp
HEADERS = src/shell.h src/batch.h src/string_utils.h
TEST_BINARIES = $(TEST_SHELL) $(TEST_STRING_UTILS) $(TEST_BATCH)

# Set the phony targets
.PHONY: all test tests run-tests run clean help

# Keep building, testing, and running as separate, explicit steps.
all: $(OSSH)

# Compile the ossh program into this directory
$(OSSH): $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) -o $@

# Compile the test_shell program
$(TEST_SHELL): tests/test_shell.cpp src/shell.cpp src/string_utils.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/test_shell.cpp src/shell.cpp src/string_utils.cpp -o $@

# Compile the test_string_utils program
$(TEST_STRING_UTILS): tests/test_string_utils.cpp src/string_utils.cpp src/string_utils.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/test_string_utils.cpp src/string_utils.cpp -o $@

# Compile the test_batch program
$(TEST_BATCH): tests/test_batch.cpp src/batch.cpp src/shell.cpp src/string_utils.cpp src/batch.h $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/test_batch.cpp src/batch.cpp src/shell.cpp src/string_utils.cpp -o $@

# Run the test programs
test: $(TEST_BINARIES)
	./$(TEST_SHELL)
	./$(TEST_STRING_UTILS)
	./$(TEST_BATCH)

# Run the test_string_utils program
tests run-tests: test

# Run the ossh program
run: $(OSSH)
	./$(OSSH)

clean:
	rm -f $(OSSH) $(TEST_BINARIES)
	rm -rf build

