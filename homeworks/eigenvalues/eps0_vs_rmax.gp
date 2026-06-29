set terminal pdfcairo enhanced font "Helvetica,14"
set output "eps0_vs_rmax.pdf"

set title "ground state energy {/Symbol e}_0 while sweeping over r_{max}"
set xlabel "r_{max}"
set ylabel "{/Symbol e}_0"
set grid

plot 'eps0_vs_rmax.dat' using 2:3 with linespoints title "data"