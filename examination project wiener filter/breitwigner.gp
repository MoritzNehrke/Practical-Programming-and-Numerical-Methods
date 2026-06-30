set terminal pdfcairo enhanced font "Helvetica,14"
set output "breitwigner.pdf"

set title "Noisy breit wigner signal"
set xlabel "x"
set ylabel "y"
set grid
set key outside

plot \
    "breitwigner.dat" using 1:3 with lines linewidth 3 lc rgb "#99000000" title "bw noisy signal", \
    "breitwigner.dat" using 1:4 with lines title "amp filtered", \
    "breitwigner.dat" using 1:5 with lines title "freq filtered", \
    "breitwigner.dat" using 1:2 with lines dashtype 2 lc rgb "black" title "original bw"