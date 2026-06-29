CXX = clang++ -std=c++23
CC = $(CXX)
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt Plot

main: main.o

Out.txt erf.dat erf1.dat &: main
	./main > Out.txt

Plot: erf.dat erf1.dat
	gnuplot erf.gp
	gnuplot erf1.gp

clean:
	rm -f main *.o *.dat Out.txt *.pdf

.PHONY: all clean Plot