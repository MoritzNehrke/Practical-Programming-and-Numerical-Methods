CXX = clang++ -std=c++23
CC = $(CXX)
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt Plot

Plot: test.dat pend.dat star1.dat star2.dat star3.dat threebody.dat
	gnuplot test.gp
	gnuplot pend.gp
	gnuplot star1.gp
	gnuplot star2.gp
	gnuplot star3.gp
	gnuplot threebody.gp

main.o: linearalgebra.h 
linearalgebra.o: linearalgebra.h
main: main.o linearalgebra.o

Out.txt test.dat pend.dat star1.dat star2.dat star3.dat threebody.dat &: main
	./main > Out.txt

clean:
	rm -f main *.o *.dat Out.txt *.pdf

.PHONY: all Plot clean