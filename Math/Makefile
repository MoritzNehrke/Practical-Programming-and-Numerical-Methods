# --------------------------------------------- 
# Makefile for a trying simple math in C++
# ---------------------------------------------

CXX = clang++ -std=c++20
CXXFLAGS = -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt

main: main.o sfuns.o
	$(CXX) $(CXXFLAGS) main.o sfuns.o $(LDLIBS) -o main

sfuns.o: sfuns.h sfuns.cc
	$(CXX) $(CXXFLAGS) -c sfuns.cc -o sfuns.o

clean: 
	$(RM) main main.o sfuns.o Out.txt