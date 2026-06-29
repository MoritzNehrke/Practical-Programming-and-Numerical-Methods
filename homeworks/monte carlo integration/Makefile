CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt Plot

Out.txt circle.dat: main
	./main > Out.txt

Plot: circle.dat
	gnuplot circle.gp

main: main.o 

clean: 
	rm -f main *.o *.dat Out.txt *.pdf

.PHONY: all clean