CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt Plot times.dat

Out.txt: main
	./main > Out.txt

main.o: linearalgebra.h 
linearalgebra.o: linearalgebra.h
main: main.o linearalgebra.o

# The sweeping part is AI generated out of convience

RMAX_FIXED = 20
DR_VALUES  = 0.5 0.4 0.3 0.25 0.2 0.15 0.1 

DR_FIXED    = 0.1
RMAX_VALUES = 3 3.5 4 4.5 5 6 7 8 9 10

NVALUES = 100 150 200 250 300 350 400

eps0_vs_dr.dat: main
	rm -f eps0_vs_dr.dat
	for dr in $(DR_VALUES); do \
		./main -rmax $(RMAX_FIXED) -dr $$dr | grep '^EPS0' | cut -d' ' -f2- >> eps0_vs_dr.dat; \
	done

eps0_vs_rmax.dat: main
	rm -f eps0_vs_rmax.dat
	for rmax in $(RMAX_VALUES); do \
		./main -rmax $$rmax -dr $(DR_FIXED) | grep '^EPS0' | cut -d' ' -f2- >> eps0_vs_rmax.dat; \
	done

times.dat: main
	rm -f times.dat
	for N in $(NVALUES); do \
		gtime --format "$$N %e" --output times.dat --append -- ./main -N $$N > /dev/null; \
	done

sweeps: eps0_vs_dr.dat eps0_vs_rmax.dat

RMAX_STD = 50
DR_STD   = 0.1

wavefunctions.dat: main
	./main -rmax $(RMAX_STD) -dr $(DR_STD) -wavefile > /dev/null

Plot: eps0_vs_dr.dat eps0_vs_rmax.dat wavefunctions.dat times.dat
	gnuplot eps0_vs_dr.gp
	gnuplot eps0_vs_rmax.gp
	gnuplot wavefunctions.gp
	gnuplot times.gp

clean:
	rm -f main *.o *.dat Out.txt *.pdf

.PHONY: sweeps clean