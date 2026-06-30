set terminal pdfcairo enhanced font "Helvetica,14"
set output "lambda.pdf"

set title "lambdas for different noise strengths"
set xlabel "noise strength"
set ylabel "lambda"
set grid
set key outside

f(x) = a*x
fit f(x) "lambda.dat" using 1:2 via a

plot \
    "lambda.dat" using 1:2 with points title "lambda", \
    f(x) with lines dashtype 2 lc rgb "#99000000" title "linear fit"
