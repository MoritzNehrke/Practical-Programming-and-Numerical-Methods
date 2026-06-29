set terminal pdfcairo enhanced font "Helvetica,14"
set output "wavefunctions.pdf"

set title "3 lowest reduced radial wavefunction"
set xlabel "r"
set ylabel "f(r)"
set grid
set key top right


plot \
  'wavefunctions.dat' using 1:2 with lines linewidth 2 lc rgb "red" title "f_0 numeric", \
  'wavefunctions.dat' using 1:5 with lines linewidth 2 lc rgb "yellow" dashtype 2 title "f_0 exact", \
  'wavefunctions.dat' using 1:3 with lines linewidth 2 lc rgb "blue" title "f_1 numeric", \
  'wavefunctions.dat' using 1:6 with lines linewidth 2 lc rgb "purple" dashtype 2 title "f_1 exact", \
  'wavefunctions.dat' using 1:4 with lines linewidth 2 lc rgb "green" title "f_2 numeric", \
  'wavefunctions.dat' using 1:7 with lines linewidth 2 lc rgb "black" dashtype 2 title "f_2 exact"
