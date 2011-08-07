#set term postscript eps
set output "graficoSenosEspectro.eps"


set size 1, 2
set multiplot


set size 1,0.4
set origin 0,2
set xlabel "tiempo"
set ylabel "Amplitud"
unset key
unset xtics
unset ytics
set title "Seno a 10Hz"
plot [0:200] "seno1.mat" with lines

set size 1,0.4
set origin 0,1.55
set title "Seno a 30Hz"
plot [0:200] "seno2.mat" with lines

set size 1,0.4
set origin 0,1.1
set title "Seno 10Hz + Seno 30Hz"
plot [0:200] "seno3.mat" with lines

set size 1,0.6
set origin 0,0.47
set xtics auto
set ytics auto
set xlabel "Frecuencia"
set ylabel "Intensidad"
set title "Espectro de frecuencias"
plot [0:100]"espectro.mat" with lines

unset multiplot
