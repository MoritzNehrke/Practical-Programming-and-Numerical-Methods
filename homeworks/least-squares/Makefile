CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt Plot

Out.txt: main
	./main > Out.txt

224Ra.dat 224Rafit.dat: main
	./main

Plot: 224Ra.dat 224Rafit.dat
	gnuplot decay.gp

main.o: linearalgebra.h 
linearalgebra.o: linearalgebra.h
main: main.o linearalgebra.o

clean:
	rm -f main *.o *.dat Out.txt *.pdf

.PHONY: all Plot clean