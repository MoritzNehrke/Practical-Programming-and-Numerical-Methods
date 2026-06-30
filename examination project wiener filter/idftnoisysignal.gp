set terminal pdfcairo enhanced font "Helvetica,14"
set output "idftnoisysignal.pdf"

set title "Inv. DFT of the DFT of and the signal"
set xlabel "x"
set ylabel "y"
set grid
set key outside

plot \
    "noisysignal.dat" using 1:2 with lines linewidth 3 lc rgb "#99000000"title "noisy signal", \
    "dftnoisysignal.dat" using 1:4 with lines title "iDFT(DFT(noisy signal))" 
