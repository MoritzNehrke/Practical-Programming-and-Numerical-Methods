set terminal pdfcairo enhanced font "Helvetica,14"
set output "pend.pdf"

set title "testing the algorithm for a pendulum with friction"
set xlabel "t"
set ylabel "theta/omega"
set grid

plot \
    'pend.dat' using 1:2 with lines title "theta", \
    'pend.dat' using 1:3 with lines title "omega"
