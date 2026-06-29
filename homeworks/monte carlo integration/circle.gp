set terminal pdfcairo enhanced font "Helvetica,14"
set output "circle.pdf"

set title "error of the unit circle are using plain MC and quasi-random MC"
set xlabel "N"
set ylabel "error"
set grid
set key outside
set logscale x 10
set logscale y 10

plot \
    'circle.dat' using 1:3 with linespoints pt 7 title "estimated perror", \
    'circle.dat' using 1:8 with lines lc rgb "#99000000" dashtype 2 title "1/sqrt(N)", \
    'circle.dat' using 1:6 with linespoints pt 7 title "estimated qerror", \
    'circle.dat' using 1:7 with linespoints pt 5 title "actual qerror", \
    'circle.dat' using 1:4 with linespoints pt 5 title "actual perror"

