CXX = g++
CXXFLAGS = -std=c++17

OSSH = ossh
NORMALIZE_TEST = tests/test_normalize
TRIM_TEST = tests/test_trim
CORE_TEST = tests/core_tests

.PHONY: all test tests run clean

all: $(OSSH) test

$(OSSH): main.cpp core/core.cpp utils/normalize.cpp utils/trim.cpp
	$(CXX) $(CXXFLAGS) main.cpp core/core.cpp utils/normalize.cpp utils/trim.cpp -o $(OSSH)

$(NORMALIZE_TEST): tests/test_normalize.cpp utils/normalize.cpp
	$(CXX) $(CXXFLAGS) tests/test_normalize.cpp utils/normalize.cpp -o $(NORMALIZE_TEST)

$(TRIM_TEST): tests/test_trim.cpp utils/trim.cpp
	$(CXX) $(CXXFLAGS) tests/test_trim.cpp utils/trim.cpp -o $(TRIM_TEST)

$(CORE_TEST): tests/core_tests.cpp core/core.cpp utils/normalize.cpp utils/trim.cpp
	$(CXX) $(CXXFLAGS) tests/core_tests.cpp core/core.cpp utils/normalize.cpp utils/trim.cpp -o $(CORE_TEST)

test: $(NORMALIZE_TEST) $(TRIM_TEST) $(CORE_TEST)
	./$(NORMALIZE_TEST)
	./$(TRIM_TEST)
	./$(CORE_TEST)

tests: test

run: $(OSSH)
	./$(OSSH)

clean:
	rm -f $(OSSH) $(NORMALIZE_TEST) $(TRIM_TEST) $(CORE_TEST)
