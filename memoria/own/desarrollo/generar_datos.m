
captureFreq = 500

t = 0:1/captureFreq:1;
samples = size(t)(2);

x1 = sin(2*pi*10*t);
fd = fopen("seno1.mat", "wt");
fprintf(fd, "%14.6f\n", x1);
fclose(fd);

x2 = sin(2*pi*30*t);
fd = fopen("seno2.mat", "wt");
fprintf(fd, "%14.6f\n", x2);
fclose(fd);

x = x1 + x2;
fd = fopen("seno3.mat", "wt");
fprintf(fd, "%14.6f\n", x);
fclose(fd);

Y = fft(x,samples);

Pyy = Y.*conj(Y)/samples;
f = captureFreq / samples * (0:samples/2);

plot(f,Pyy(1:samples/2 + 1));

fd = fopen("espectro.mat", "wt");
for x = (1:samples/2 + 1)
  fprintf(fd, "%14.6f %14.6f\n", f(x), Pyy(x));
endfor
fclose(fd);
