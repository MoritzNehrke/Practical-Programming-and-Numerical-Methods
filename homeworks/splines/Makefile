CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt Plot

Out.txt interpolation.dat: main
	./main > Out.txt

Plot: interpolation.dat lspline.gp qspline.gp fqspline.gp
	gnuplot lspline.gp
	gnuplot qspline.gp
	gnuplot fqspline.gp

main.o: linearalgebra.h 
linearalgebra.o: linearalgebra.h
main: main.o linearalgebra.o

clean: 
	rm -f main *.o *.dat Out.txt *.pdf

.PHONY: all Plot clean