set terminal pdfcairo enhanced font "Helvetica,14"
set output "fqspline.pdf"

set title "visualization of the quadratic spline(FS)"
set xlabel "x"
set ylabel "y"
set grid
set yrange [-1.1:1.1]

f(x) = cos(x)

plot \
    'interpolation.dat' using 1:6 with lines linewidth 2 lc rgb "#990000ff" title "h", \
    f(x) with lines dashtype 2 lc rgb "blue" title "cosx"

    
