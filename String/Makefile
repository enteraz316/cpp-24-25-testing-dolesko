CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -g -fsanitize=address,undefined#,leak

STOP_AFTER_FAIL ?= 0
HARDCORE_TESTING ?= 1

CPPFLAGS := -DSTOP_AFTER_FAIL=$(STOP_AFTER_FAIL) -DHARDCORE_TESTING=$(HARDCORE_TESTING)

SRCS := test.cpp test_driver.cpp test_cases.cpp
OBJS := $(SRCS:.cpp=.o)

all: test clean

test: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	./test

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) test
