CXX = g++
CXXFLAGS = -std=c++17

OSSH = assignment_1/ossh
NORMALIZE_TEST = assignment_1/tests/test_normalize
CORE_TEST = assignment_1/tests/core_tests

.PHONY: all test run clean

all: $(OSSH) $(NORMALIZE_TEST) $(CORE_TEST)

$(OSSH): assignment_1/main.cpp assignment_1/core/core.cpp assignment_1/utils/normalize.cpp assignment_1/utils/trim.cpp
	$(CXX) $(CXXFLAGS) assignment_1/main.cpp assignment_1/core/core.cpp assignment_1/utils/normalize.cpp assignment_1/utils/trim.cpp -o $(OSSH)

$(NORMALIZE_TEST): assignment_1/tests/test_normalize.cpp assignment_1/utils/normalize.cpp
	$(CXX) $(CXXFLAGS) assignment_1/tests/test_normalize.cpp assignment_1/utils/normalize.cpp -o $(NORMALIZE_TEST)

$(CORE_TEST): assignment_1/tests/core_tests.cpp assignment_1/core/core.cpp assignment_1/utils/normalize.cpp assignment_1/utils/trim.cpp
	$(CXX) $(CXXFLAGS) assignment_1/tests/core_tests.cpp assignment_1/core/core.cpp assignment_1/utils/normalize.cpp assignment_1/utils/trim.cpp -o $(CORE_TEST)

test: $(NORMALIZE_TEST) $(CORE_TEST)
	./$(NORMALIZE_TEST)
	./$(CORE_TEST)

run: $(OSSH)
	./$(OSSH)

clean:
	rm -f $(OSSH) $(NORMALIZE_TEST) $(CORE_TEST)
