set terminal pdf
set output "imagen_hann.pdf"

set xlabel "Muestras"
set ylabel "Amplitud"
unset key;
unset xtics;

plot [0:50] 0.5 * (1 - cos((2 * pi * x) / (50))) with lines lw 2;