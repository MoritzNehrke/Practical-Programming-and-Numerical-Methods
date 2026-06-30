set terminal pdfcairo enhanced font "Helvetica,14"
set output "filteredsignal.pdf"

set title "Generated noisy signal and applied filter"
set xlabel "x"
set ylabel "y"
set grid
set key outside

f(x) = cos(2*pi*x) 

plot \
    "filteredsignal.dat" using 1:2 with lines linewidth 3 lc rgb "#99000000"title "noisy signal", \
    "filteredsignal.dat" using 1:3 with lines lc rgb "red" title "freq filter", \
    f(x) with lines dashtype 2 lc rgb "#70000000" title "cos(x)", \
    "filteredsignal.dat" using 1:4 with lines lc rgb "blue" title "amp filter"