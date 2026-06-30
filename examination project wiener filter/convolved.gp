set terminal pdfcairo enhanced font "Helvetica,14"
set output "convolved.pdf"

set title "Convoluted noisy breit wigner signal"
set xlabel "x"
set ylabel "y"
set grid
set key outside

plot \
    "convolved.dat" using 1:4 with lines title "convolved + noise", \
    "convolved.dat" using 1:3 with lines title "convolved", \
    "convolved.dat" using 1:2 with lines dashtype 2 lc rgb "black" title "original bw"