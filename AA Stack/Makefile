CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined,leak -std=c++20
# CXXFLAGS = -fsanitize=address,undefined,leak -std=c++20

TEST_TILL_END ?= 0 # 1 - run all tests, 0 - stop after first failure

all: AA test clean

AA: AA.cpp
	$(CXX) $(CXXFLAGS) AA.cpp -o solution

test: test.cpp AA
	$(CXX) $(CXXFLAGS) -DTEST_TILL_END=$(TEST_TILL_END) test.cpp -o test
	./test

clean:
	rm -f solution test
