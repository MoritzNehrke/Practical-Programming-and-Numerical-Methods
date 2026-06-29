set terminal pdfcairo enhanced font "Helvetica,14"
set output "qspline.pdf"

set title "visualization of the quadratic spline(OOP)"
set xlabel "x"
set ylabel "y"
set grid
set yrange [-1.1:1.1]

f(x) = cos(x)
g(x) = sin(x)

plot \
    'interpolation.dat' using 1:4 with lines linewidth 2 lc rgb "#990000ff" title "g", \
    'interpolation.dat' using 1:5 with lines linewidth 2 lc rgb "#99ff0000" title "G", \
    f(x) with lines dashtype 2 lc rgb "blue" title "cosx", \
    g(x) with lines dashtype 2 lc rgb "red" title "sinx"
    
