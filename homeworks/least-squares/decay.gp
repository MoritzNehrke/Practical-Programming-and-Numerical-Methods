set terminal pdfcairo enhanced font "Helvetica,14"
set output "decay.pdf"

set title "decay of 224-Ra"
set xlabel "t in days"
set ylabel "activity in relative units"
set grid

plot\
    '224Rafit.dat' using 1:2 with lines title "fit",\
    '224Rafit.dat' using 1:3 with lines title "fitmaximum",\
    '224Rafit.dat' using 1:4 with lines title "fitminimum",\
    '224Ra.dat' using 1:2:3 with yerrorbars pt 0 ps 0.8 lc rgb "blue" title "meas."