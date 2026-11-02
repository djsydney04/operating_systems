# Makefile for the assignment 2 multilevel queue scheduler

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
CPPFLAGS += -Isrc -Iutils

LIB_SOURCES = $(filter-out src/main.cpp, $(wildcard src/*.cpp)) $(wildcard utils/*.cpp)
HEADERS = $(wildcard src/*.h utils/*.h tests/unit/*.h)
TESTS = $(basename $(notdir $(wildcard tests/unit/test_*.cpp)))

INPUT = tests/fixtures/input.txt

.PHONY: all run run-all test clean

all: scheduler

scheduler: src/main.cpp $(LIB_SOURCES) $(HEADERS)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/main.cpp $(LIB_SOURCES) -o $@

run: scheduler
	./scheduler $(INPUT)

# Run every input in tests/fixtures and save each result to output/ for the submission.
run-all: scheduler
	@mkdir -p output
	@for f in tests/fixtures/*.txt; do \
		./scheduler $$f > output/$$(basename $$f) || exit 1; \
		echo "wrote output/$$(basename $$f)"; \
	done

test_%: tests/unit/test_%.cpp $(LIB_SOURCES) $(HEADERS)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(LIB_SOURCES) -o $@

test: $(TESTS)
	@for t in $(TESTS); do echo "./$$t"; ./$$t || exit 1; done

clean:
	rm -f scheduler $(TESTS)
