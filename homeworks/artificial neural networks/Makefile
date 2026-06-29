CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

all: Out.txt Plot

Out.txt anntest.dat: main
	./main > Out.txt


main.o: linearalgebra.h 
linearalgebra.o: linearalgebra.h
main: main.o linearalgebra.o

Plot: anntest.dat
	gnuplot anntest.gp
	gnuplot annb.gp



clean: 
	rm -f main *.o Out.txt *.dat *.pdf

.PHONY: all clean