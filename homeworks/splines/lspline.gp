set terminal pdfcairo enhanced font "Helvetica,14"
set output "lspline.pdf"

set title "visualization of the linear spline"
set xlabel "x"
set ylabel "y"
set grid
set yrange [-1.1:1.1]

f(x) = cos(x)
g(x) = sin(x)

plot \
    'interpolation.dat' using 1:2 with lines linewidth 2 lc rgb "#990000ff" title "f", \
    'interpolation.dat' using 1:3 with lines linewidth 2 lc rgb "#99ff0000" title "F", \
    f(x) with lines dashtype 2 lc rgb "blue" title "cosx", \
    g(x) with lines dashtype 2 lc rgb "red" title "sinx"
    
