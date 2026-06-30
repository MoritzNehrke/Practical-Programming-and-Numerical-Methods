set terminal pdfcairo enhanced font "Helvetica,14"
set output "deconvolved.pdf"

set title "deconvolved breit wigner signal"
set xlabel "x"
set ylabel "y"
set grid
set key outside

plot \
    "deconvolved.dat" using 1:4 with lines title "naive deconvolution", \
    "deconvolved.dat" using 1:2 with lines dashtype 2 lc rgb "black" title "original bw"