set terminal pdfcairo enhanced font "Helvetica,14"
set output "erf.pdf"

set title "calculated error function"
set xlabel "x"
set ylabel "erf(x)"
set grid
set key outside

f(x) = erf(x)

plot \
    'erf.dat' using 1:2 with lines dashtype 2 lc rgb "red" title "calc. erf(x)", \
    f(x) with lines lc rgb "#99ff0000"title "erf(x)"
