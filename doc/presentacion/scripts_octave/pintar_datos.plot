set terminal pdf size 8,6;
set output "imagen_senosEspectro.pdf";

set size 1,1;
set multiplot layout 2,2;

set xlabel "tiempo";
set ylabel "Amplitud";
unset key;
unset xtics;
#unset ytics;

###################################
## Primer Seno (10Hz)

set title "Seno, Frecuencia = 10Hz, Amplitud = 5";
plot [0:200] "seno1.mat" with lines lw 2;

###################################
## Segundo Seno (30Hz)

#set size 1,0.4;
#set origin 0,1.55;

set title "Seno, Frecuencia = 30Hz, Amplitud = 2.5";
plot [0:200] "seno2.mat" with lines lw 2;


###################################
## Suma de senos
#set size 1,0.4;
#set origin 0,1.1;

set title "Seno 10Hz + Seno 30Hz";
plot [0:200] "seno3.mat" with lines lw 2;


###################################
## ESPECTRO

#set size 1,0.6;
#set origin 0,0.47;

set xtics auto;
set ytics auto;
set xlabel "Frecuencia";
set ylabel "Intensidad";
set title "Espectro de frecuencias";
plot [0:100]"espectro.mat" with lines lw 2;

unset multiplot;
