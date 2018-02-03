# Makefile

CXX ?= c++
CXXFLAGS ?= -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -Qunused-arguments -std=c++11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow

.PHONY: all
all: main

main: helpers.cpp helpers.hpp main.cpp
	$(CXX) $(CXXFLAGS) -o main helpers.cpp main.cpp

.PHONY: clean
clean:
	rm -f main
