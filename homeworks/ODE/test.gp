set terminal pdfcairo enhanced font "Helvetica,14"
set output "test.pdf"

set title "testing the algorithm for u'' = -u, u(0) = 1 and u'(0) = 0 "
set xlabel "x"
set ylabel "y"
set grid

plot 'test.dat' using 1:2 with lines title "data"