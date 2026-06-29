set terminal pdfcairo enhanced font "Helvetica,14"
set output "erf1.pdf"

set title "accuracy of erf(1) for different acc"
set xlabel "acc"
set ylabel "acc_{erf}"
set grid
set key outside
set logscale x 10
set logscale y 10

plot \
    'erf1.dat' using 1:2 with lines lc rgb "blue" title "acc_{erf}", \
    'erf1.dat' using 1:1 with lines lc rgb "#99000000" dashtype 2 title "acc"
