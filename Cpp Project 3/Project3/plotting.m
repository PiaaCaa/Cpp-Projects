file = fopen("outfile.bin");
A=fread(file,[2,101],'double');

f =@ (x) (0.5 * 1 ./ (1+exp(-3*(x+6))));


g =@ (x) (0.5 * 1 ./ (1+exp(3*x)));

x = -10:0.01:-3;
xx = -3:0.01:5;


figure(1);
plot(A(1,:), A(2,:), "-r", x, f(x), "-b", xx, g(xx),"-g");
