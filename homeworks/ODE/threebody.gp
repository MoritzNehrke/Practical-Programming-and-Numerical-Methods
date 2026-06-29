set terminal pdfcairo enhanced font "Helvetica,14"
set output "threebody.pdf"

set title "Solution of three-body problem"
set xlabel "x"
set ylabel "y"
set grid
set key outside

plot \
    'threebody.dat' using 8:9   with lines dashtype 2 title "body 1", \
    'threebody.dat' using 10:11 with lines dashtype 1 title "body 2", \
    'threebody.dat' using 12:13 with lines dashtype 0 title "body 3"
