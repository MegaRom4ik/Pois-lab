CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Werror
ifeq ($(shell uname -s),Darwin)
CXX = $(shell xcrun --find clang++)
CXXFLAGS += -isysroot $(shell xcrun --sdk macosx --show-sdk-path)
LLVM_COV = $(shell xcrun --find llvm-cov)
LLVM_PROFDATA = $(shell xcrun --find llvm-profdata)
endif
DOMAIN = lab1/vector/Vector3.cpp lab1/tictactoe/TicTacToe.cpp
TEST_SOURCES = lab1/tests/vector_tests.cpp lab1/tests/tictactoe_tests.cpp
HEADERS = lab1/vector/Vector3.hpp lab1/tictactoe/TicTacToe.hpp
LLVM_COV ?= llvm-cov
LLVM_PROFDATA ?= llvm-profdata

.PHONY: all test coverage docs clean
all: build/vector_cli build/tictactoe_cli

build:
	mkdir -p build

build/vector_cli: lab1/vector/main.cpp lab1/vector/Vector3.cpp $(HEADERS) lab1/cli/Input.hpp | build
	$(CXX) $(CXXFLAGS) lab1/vector/main.cpp lab1/vector/Vector3.cpp -o $@

build/tictactoe_cli: lab1/tictactoe/main.cpp lab1/tictactoe/TicTacToe.cpp $(HEADERS) lab1/cli/Input.hpp | build
	$(CXX) $(CXXFLAGS) lab1/tictactoe/main.cpp lab1/tictactoe/TicTacToe.cpp -o $@

build/doctest.h: | build
	curl --fail --location --retry 3 https://raw.githubusercontent.com/doctest/doctest/v2.4.11/doctest/doctest.h -o $@

build/tests: $(TEST_SOURCES) $(DOMAIN) $(HEADERS) build/doctest.h
	$(CXX) $(CXXFLAGS) -Ibuild $(TEST_SOURCES) $(DOMAIN) -o $@

test: build/tests
	./build/tests

build/coverage_tests: $(TEST_SOURCES) $(DOMAIN) $(HEADERS) build/doctest.h
	$(CXX) $(CXXFLAGS) -O0 -g -fprofile-instr-generate -fcoverage-mapping -Ibuild $(TEST_SOURCES) $(DOMAIN) -o $@

coverage: build/coverage_tests
	LLVM_PROFILE_FILE=build/tests.profraw ./build/coverage_tests
	$(LLVM_PROFDATA) merge -sparse build/tests.profraw -o build/tests.profdata
	$(LLVM_COV) report ./build/coverage_tests -instr-profile=build/tests.profdata $(DOMAIN)
	$(LLVM_COV) export ./build/coverage_tests -instr-profile=build/tests.profdata $(DOMAIN) > build/coverage.json
	python3 scripts/check_coverage.py build/coverage.json
	$(LLVM_COV) show ./build/coverage_tests -instr-profile=build/tests.profdata $(DOMAIN) -format=html -output-dir=build/coverage

docs:
	doxygen Doxyfile

clean:
	rm -rf build

LAB2_SOURCES = $(wildcard lab2/src/*.cpp)
LAB2_HEADERS = $(wildcard lab2/include/*.hpp)
LAB2_TESTS = $(wildcard lab2/tests/*.cpp)

.PHONY: lab2 test-lab2 coverage-lab2 docs-lab2 check-lab2-model
lab2: build/cooking_cli

build/cooking_cli: lab2/main.cpp $(LAB2_SOURCES) $(LAB2_HEADERS) | build
	$(CXX) $(CXXFLAGS) -Ilab2/include lab2/main.cpp $(LAB2_SOURCES) -o $@

build/cooking_tests: $(LAB2_TESTS) $(LAB2_SOURCES) $(LAB2_HEADERS) build/doctest.h
	$(CXX) $(CXXFLAGS) -Ibuild -Ilab2/include $(LAB2_TESTS) $(LAB2_SOURCES) -o $@

test-lab2: build/cooking_tests
	./build/cooking_tests

build/cooking_coverage_tests: $(LAB2_TESTS) $(LAB2_SOURCES) $(LAB2_HEADERS) build/doctest.h
	$(CXX) $(CXXFLAGS) -O0 -g -fprofile-instr-generate -fcoverage-mapping -Ibuild -Ilab2/include $(LAB2_TESTS) $(LAB2_SOURCES) -o $@

coverage-lab2: build/cooking_coverage_tests
	LLVM_PROFILE_FILE=build/cooking.profraw ./build/cooking_coverage_tests
	$(LLVM_PROFDATA) merge -sparse build/cooking.profraw -o build/cooking.profdata
	$(LLVM_COV) export ./build/cooking_coverage_tests -instr-profile=build/cooking.profdata $(LAB2_SOURCES) > build/cooking-coverage.json
	python3 scripts/check_lab2.py coverage build/cooking-coverage.json
	$(LLVM_COV) show ./build/cooking_coverage_tests -instr-profile=build/cooking.profdata $(LAB2_SOURCES) -format=html -output-dir=build/cooking-coverage

docs-lab2:
	doxygen lab2/Doxyfile

check-lab2-model:
	python3 scripts/check_lab2.py model lab2

all: lab2
test: test-lab2
coverage: coverage-lab2
docs: docs-lab2

LAB3_SOURCES = $(wildcard lab3/src/*.cpp)
LAB3_HEADERS = $(wildcard lab3/include/*.hpp)
LAB3_TESTS = $(wildcard lab3/tests/*.cpp)

.PHONY: lab3 test-lab3 coverage-lab3 docs-lab3 check-lab3-model
lab3: build/fitness_cli

build/fitness_cli: lab3/main.cpp $(LAB3_SOURCES) $(LAB3_HEADERS) lab1/cli/Input.hpp | build
	$(CXX) $(CXXFLAGS) -Ilab3/include lab3/main.cpp $(LAB3_SOURCES) -o $@

build/fitness_tests: $(LAB3_TESTS) $(LAB3_SOURCES) $(LAB3_HEADERS) build/doctest.h
	$(CXX) $(CXXFLAGS) -Ibuild -Ilab3/include $(LAB3_TESTS) $(LAB3_SOURCES) -o $@

test-lab3: build/fitness_tests
	./build/fitness_tests

build/fitness_coverage_tests: $(LAB3_TESTS) $(LAB3_SOURCES) $(LAB3_HEADERS) build/doctest.h
	$(CXX) $(CXXFLAGS) -O0 -g -fprofile-instr-generate -fcoverage-mapping -Ibuild -Ilab3/include $(LAB3_TESTS) $(LAB3_SOURCES) -o $@

coverage-lab3: build/fitness_coverage_tests
	LLVM_PROFILE_FILE=build/fitness.profraw ./build/fitness_coverage_tests
	$(LLVM_PROFDATA) merge -sparse build/fitness.profraw -o build/fitness.profdata
	$(LLVM_COV) export ./build/fitness_coverage_tests -instr-profile=build/fitness.profdata $(LAB3_SOURCES) > build/fitness-coverage.json
	python3 scripts/check_lab3.py coverage build/fitness-coverage.json
	$(LLVM_COV) show ./build/fitness_coverage_tests -instr-profile=build/fitness.profdata $(LAB3_SOURCES) -format=html -output-dir=build/fitness-coverage

docs-lab3:
	doxygen lab3/Doxyfile

check-lab3-model:
	python3 scripts/check_lab3.py model lab3

all: lab3
test: test-lab3
coverage: coverage-lab3
docs: docs-lab3
