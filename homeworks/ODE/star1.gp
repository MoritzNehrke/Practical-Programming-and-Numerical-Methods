set terminal pdfcairo enhanced font "Helvetica,14"
set output "star1.pdf"

set title "Newtonian circular motion"
set xlabel "x"
set ylabel "y"
set grid

plot "star1.dat" using (1/$2)*cos($1):(1/$2)*sin($1) with lines notitle 