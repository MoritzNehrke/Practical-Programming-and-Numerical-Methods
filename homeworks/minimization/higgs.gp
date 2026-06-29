set terminal pdfcairo enhanced font "Helvetica,14"
set output "higgs.pdf"

set title "Fitted Breit Wigner function compared to the measurement"
set xlabel "E"
set ylabel "F(E)"
set grid
set key outside

plot\
    'higgsfit.dat' using 1:2 with lines lc rgb "red" title "fit",\
    'higgs.txt' using 1:2:3 with yerrorbars pt 0 lc rgb "blue" title "measurement"