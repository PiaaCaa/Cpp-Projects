file1 = fopen("grid_out.bin");
grid=fread(file1,[2,51*21],'double');

file2 = fopen("curve_out.bin");
curvebase=fread(file2,[2,400],'double');

file3 = fopen("u_out.bin");
U=fread(file3,[51,21],'double');

file4 = fopen("dux_out.bin");
Ux=fread(file4,[51,21],'double');

file5 = fopen("duy_out.bin");
Uy=fread(file5,[51,21],'double');

file6 = fopen("dlaplace_out.bin");
Unabla=fread(file6,[51,21],'double');

f =@(x,y) (sin((x/10).^2) .* cos(x/10) + y);
dfx =@(x,y) (1/50 .* (x.* cos(x/10) .* cos((x.^2)/100) - 5 .* sin(x/10) .* sin((x.^2)/100)));
% nablaf =@

% figure(1);
% plot(B(1,:), B(2,:), "-r", "LineWidth",2);
% hold on;
% scatter(A(1,:), A(2,:),15,"blue","filled");
% grid on;
% xlabel("x");
% ylabel("y");
% title("50x20 Grid");


X = reshape(grid(1,:), [51,21]); 
Y = reshape(grid(2,:), [51,21]);

dfx(-10,0)

%(f()) / ()

figure(1);
subplot(2,2,1);
surf(X, Y, U);

subplot(2,2,2);
surf(X, Y, Uy);

subplot(2,2,3);
surf(X,Y,Ux);
% 
% subplot(2,2,4);
% surf(X,Y,dfx(X,Y));

%subplot(2,2,3);
%surf(X,Y,Uy);

subplot(2,2,4);
surf(X,Y,Unabla);
