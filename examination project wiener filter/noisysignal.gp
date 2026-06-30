set terminal pdfcairo enhanced font "Helvetica,14"
set output "noisysignal.pdf"

set title "Generated noisy signal"
set xlabel "x"
set ylabel "y"
set grid
set key outside

plot "noisysignal.dat" using 1:2 with lines title "noisy signal" 