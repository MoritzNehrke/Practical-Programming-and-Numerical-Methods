CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

all: Out.txt Plot

Out.txt wavefunction.dat &: main
	./main > Out.txt


main.o: linearalgebra.h 
linearalgebra.o: linearalgebra.h
main: main.o linearalgebra.o

Plot: wavefunction.dat
	gnuplot wavefunction.gp

clean: 
	rm -f main *.o Out.txt wavefunction.dat *.pdf

.PHONY: all clean Plot