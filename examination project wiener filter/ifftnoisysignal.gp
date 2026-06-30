set terminal pdfcairo enhanced font "Helvetica,14"
set output "ifftnoisysignal.pdf"

set title "Inv. FFT of the FFT of and the signal"
set xlabel "x"
set ylabel "y"
set grid
set key outside

plot \
    "noisysignal.dat" using 1:2 with lines linewidth 3 lc rgb "#99000000"title "noisy signal", \
    "fftnoisysignal.dat" using 1:4 with lines title "iFFT(FFT(noisy signal))" 
