# ---------------------------------------------
# Makefile for a the machine epsilon program
# ---------------------------------------------

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt

main: main.cc comp.o
	$(CXX) $(CXXFLAGS) -o main main.cc comp.o $(LDLIBS)

comp.o: comp.h comp.cc
	$(CXX) $(CXXFLAGS) -c comp.cc -o comp.o

clean:
	rm -f main Out.txt

