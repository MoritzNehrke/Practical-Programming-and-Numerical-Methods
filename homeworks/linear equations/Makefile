CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt times.svg

Out.txt: main
	./main > Out.txt

main.o: linearalgebra.h 
linearalgebra.o: linearalgebra.h
main: main.o linearalgebra.o

out.times.data : main
	rm -f $@
	for N in 100 150 200 250 300 350 400; do \
		gtime --format "$$N %e" --output $@ --append \
		./$< -size $$N 1>out 2>err ;\
	done 

times.svg: out.times.data Makefile
	echo '\
		set terminal svg background rgb "white" ;\
		set output "$@" ;\
		set xlabel "matrix size" ;\
		set ylabel "real time" ;\
		a = 1e-9 ;\
		f(x) = a*x**3 ;\
		fit f(x) "out.times.data" using 1:2 via a ;\
		plot \
		     "out.times.data" using 1:2 with points title "times", \
		     f(x) with lines title sprintf("fit: %.3e * N^3", a) \
	'| tee log.times |gnuplot

clean:
	rm -f *.o main Out.txt out.times.data out err times.svg log.times fit.log