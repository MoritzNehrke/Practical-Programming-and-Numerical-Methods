set terminal pdfcairo enhanced font "Helvetica,14"
set output "times.pdf"

set title "runtime of the decomposition algorithm"
set xlabel "matrix size N"
set ylabel "time in s"
set grid

a = 1e-7 
f(x) = a*x**3 
fit f(x) "times.dat" using 1:2 via a

plot \
    'times.dat' using 1:2 with points title "data", \
    f(x) with lines title sprintf("fit: %.3e * N^3", a)
