set terminal pdfcairo enhanced font "Helvetica,14"
set output "star3.pdf"

set title "Relativistic precession"
set xlabel "x"
set ylabel "y"
set grid

plot "star3.dat" using (1/$2)*cos($1):(1/$2)*sin($1) with lines notitle 