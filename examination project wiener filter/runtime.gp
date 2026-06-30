set terminal pdfcairo enhanced font "Helvetica,14"
set output "runtime.pdf"

set title "runtime of the DFT and FFT routine"
set xlabel "N"
set xrange [1024:]
set ylabel "time in s (DFT)"
set grid
set key outside
set logscale x 2

set y2label "time in s (FFT)"
set y2range [0:0.05]
set y2tics

a = 1e-7 
f(x) = a*x**2 
fit f(x) "dft.times.data" using 1:2 via a
b = 1e-7
g(x) = b*x*log(x)
fit g(x) "fft.times.data" using 1:2 skip 5 via b

plot \
    'dft.times.data' using 1:2 with points title "DFT" axes x1y1, \
    f(x) with lines title "N^2 fit" axes x1y1, \
    'fft.times.data' using 1:2 with points title "FFT" axes x1y2, \
    g(x) with lines title "Nlog(N) fit" axes x1y2