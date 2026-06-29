CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

all: Out.txt Plot

Out.txt higgs.dat higgsfit.dat &: main higgs.txt
	./main < higgs.txt 1> Out.txt 2> log


main.o: linearalgebra.h 
linearalgebra.o: linearalgebra.h
main: main.o linearalgebra.o

Plot: higgsfit.dat higgs.txt higgs.gp
	gnuplot higgs.gp

clean: 
	rm -f main *.o Out.txt *.dat *.pdf log

.PHONY: all Plot clean