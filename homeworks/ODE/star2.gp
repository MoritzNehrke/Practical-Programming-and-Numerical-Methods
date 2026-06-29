set terminal pdfcairo enhanced font "Helvetica,14"
set output "star2.pdf"

set title "Newtonian elliptical motion"
set xlabel "x"
set ylabel "y"
set grid

plot "star2.dat" using (1/$2)*cos($1):(1/$2)*sin($1) with lines notitle 