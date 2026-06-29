set terminal pdfcairo enhanced font "Helvetica,14"
set output "wavefunctions.pdf"

set title "-"
set xlabel "r"
set ylabel "f(r)"
set grid
set key top right

f(x)=x*exp(-x);


plot \
    f(x) with lines linewidth 2 lc rgb "#99000000" title "f_0 exact", \
    'wavefunction.dat' using 1:2 with lines linewidth 2 lc rgb "red" dashtype 2 title "f_0 numeric"