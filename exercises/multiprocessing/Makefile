TIME = /usr/bin/time -p -o out.times -a
N = 100000000

times.svg: out.times Makefile
	echo '\
		set terminal pdfcairo ;\
		set output "performance.pdf" ;\
		set xlabel "number of threads" ;\
		set ylabel "real time" ;\
		plot \
			 "data.dat" using 1:2 with linespoints title "times" \
	'| tee log.times |gnuplot


out.times: main
	rm -f out.times threads.tmp times.tmp data.dat
	for nthreads in 1 2 3 4 5 6 7 8; do \
		echo $$nthreads >> threads.tmp ;\
		$(TIME) ./main -threads $$nthreads -terms $(N) > /dev/null ;\
	done
	grep '^real' out.times | sed 's/real //' > times.tmp
	paste threads.tmp times.tmp > data.dat

clean:
	rm -f out.times threads.tmp times.tmp data.dat main