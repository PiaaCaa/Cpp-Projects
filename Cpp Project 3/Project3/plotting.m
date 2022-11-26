file1 = fopen("grid_out.bin");
A=fread(file1,[2,51*21],'double');

file2 = fopen("curve_out.bin");
B=fread(file2,[2,400],'double');


figure(1);
plot(B(1,:), B(2,:), "-r", "LineWidth",2);
hold on;
scatter(A(1,:), A(2,:),15,"blue","filled");
grid on;
xlabel("x");
ylabel("y");
title("50x20 Grid");

