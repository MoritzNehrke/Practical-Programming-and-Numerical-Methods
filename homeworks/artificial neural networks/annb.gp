set terminal pdfcairo enhanced font "Helvetica,14"
set output "annb.pdf"

set title "testing the ANN on cos(5*x-1)*exp(-x*x)"
set xlabel "x"
set ylabel "f(x)"
set grid
set key outside

plot \
    'anntest.dat' using 1:2 with lines title "ANN fit", \
    'anntest.dat' using 1:3 with lines title "ANN derivative", \
    'anntest.dat' using 1:4 with lines title "ANN 2nd derivative", \
    'anntest.dat' using 1:5 with lines title "ANN anti-derivative"