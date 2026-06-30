set terminal pdfcairo enhanced font "Helvetica,14"
set output "wiener.pdf"

set title "wiener filter applied to convolved bw signal"
set xlabel "x"
set ylabel "y"
set grid
set key outside

plot \
    "wiener.dat" using 1:4 with lines title "lambda = 1e-4", \
    "wiener.dat" using 1:5 with lines title "lambda = 1e-3", \
    "wiener.dat" using 1:6 with lines title "lambda = 1e-2", \
    "wiener.dat" using 1:7 with lines title "lambda = 1e-1", \
    "wiener.dat" using 1:2 with lines dashtype 2 lc rgb "black" title "original bw"

set output "wienerfinal.pdf"
plot \
    "wiener.dat" using 1:6 with lines linewidth 3 lc rgb "#99000000" title "lambda = 1e-2", \
    "wiener.dat" using 1:2 with lines dashtype 2 lc rgb "black" title "original bw", \
    "wieneroptimal.dat" using 1:2 with lines title "optimal lambda"
