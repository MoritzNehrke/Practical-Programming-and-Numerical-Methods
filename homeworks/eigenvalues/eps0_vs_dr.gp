set terminal pdfcairo enhanced font "Helvetica,14"
set output "eps0_vs_dr.pdf"

set title "ground state energy {/Symbol e}_0 while sweeping over dr"
set xlabel "dr"
set ylabel "{/Symbol e}_0"
set grid

plot 'eps0_vs_dr.dat' using 1:3 with linespoints title "data"