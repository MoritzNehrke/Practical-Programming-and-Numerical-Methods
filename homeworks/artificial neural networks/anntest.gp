set terminal pdfcairo enhanced font "Helvetica,14"
set output "anntest.pdf"

set title "testing the ANN on cos(5*x-1)*exp(-x*x)"
set xlabel "x"
set ylabel "f(x)"
set grid
set key outside


f(x) = cos(5*x-1)*exp(-x*x)


plot \
    'anntest.dat' using 1:2 with lines lc rgb "green" title "ANN fit", \
    f(x) with lines lc rgb "#99000000" dashtype 2 title "function"