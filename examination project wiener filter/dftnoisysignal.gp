set terminal pdfcairo enhanced font "Helvetica,14"
set output "dftnoisysignal.pdf"

set title "DFT of the generated noisy signal"
set xlabel "f"
set xrange [0:6]
set ylabel "Y"
set grid
set key outside

set x2label "f"
set x2range [79:85]
set x2tics

plot \
    "dftnoisysignal.dat" using 2:3 with lines title "DFT (low-freq peak)" axes x1y1, \
    "dftnoisysignal.dat" using 2:3 with lines title "DFT (mirror peak)" axes x2y1 lc rgb "green"
