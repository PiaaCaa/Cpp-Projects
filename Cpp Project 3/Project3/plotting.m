file1 = fopen("grid_out.bin");
A=fread(file1,[2,51*21],'double');

file2 = fopen("curve_out.bin");
B=fread(file2,[2,400],'double');


f =@ (x) (0.5 * 1 ./ (1+exp(-3*(x+6))));


g =@ (x) (0.5 * 1 ./ (1+exp(3*x)));

x = -10:0.01:-3;
xx = -3:0.01:5;


figure(1);
plot(B(1,:), B(2,:), "-r", "LineWidth",2);
hold on;
scatter(A(1,:), A(2,:),15,"blue","filled");
grid on;
xlabel("x");
ylabel("y");
title("50x20 Grid")
%plot(A(1,:), A(2,:), '.')
%plot(B(1,:), B(2,:), "-r", x, f(x), "-b", xx, g(xx),"-g");
