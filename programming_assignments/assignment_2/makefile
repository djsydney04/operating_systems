# Makefile for the assignment 2 multilevel queue scheduler

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
CPPFLAGS += -Isrc -Iutils

SCHEDULER = scheduler
TEST_PARSE_TASK_LINE = test_parse_task_line
TEST_READY_QUEUES = test_ready_queues
LIB_SOURCES = $(filter-out src/main.cpp, $(wildcard src/*.cpp)) $(wildcard utils/*.cpp)
HEADERS = $(wildcard src/*.h utils/*.h)
INPUT_FIXTURE = tests/fixtures/input.txt

# Input file for `make run`; override with `make run INPUT=path/to/file.txt`
INPUT ?= $(INPUT_FIXTURE)

.PHONY: all run test clean

all: $(SCHEDULER)

$(SCHEDULER): src/main.cpp $(LIB_SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/main.cpp $(LIB_SOURCES) -o $@

run: $(SCHEDULER)
	./$(SCHEDULER) $(INPUT)

$(TEST_PARSE_TASK_LINE): tests/unit/test_parse_task_line.cpp utils/task_reader.cpp $(wildcard utils/*.h)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/unit/test_parse_task_line.cpp utils/task_reader.cpp -o $@

$(TEST_READY_QUEUES): tests/unit/test_ready_queues.cpp src/queues.cpp src/algorithms.cpp utils/task_reader.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/unit/test_ready_queues.cpp src/queues.cpp src/algorithms.cpp utils/task_reader.cpp -o $@

test: $(TEST_PARSE_TASK_LINE) $(TEST_READY_QUEUES)
	./$(TEST_PARSE_TASK_LINE)
	./$(TEST_READY_QUEUES)

clean:
	rm -f $(SCHEDULER) $(TEST_PARSE_TASK_LINE) $(TEST_READY_QUEUES)
