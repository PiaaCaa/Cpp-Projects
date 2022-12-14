% Choose number of grid points of the imported C++ files
N = 51;
M = 21;

% Read files from C++
file1 = fopen("grid_out.bin");
grid=fread(file1,[2,N*M],'double');

file2 = fopen("curve_out.bin");
curvebase=fread(file2,[2,400],'double');

file3 = fopen("u_out.bin");
U=fread(file3,[N,M],'double');

file4 = fopen("dux_out.bin");
Ux=fread(file4,[N,M],'double');

file5 = fopen("duy_out.bin");
Uy=fread(file5,[N,M],'double');

file6 = fopen("dlaplace_out.bin");
Unabla=fread(file6,[N,M],'double');

% Analytical function u(x,y)
f =@(x,y) (sin((x/10).^2) .* cos(x/10) + y);

% Analytical function u(x,y=0)
fx =@(x) (sin((x/10).^2) .* cos(x/10));

% Analytical derivative du/dx
dfx =@(x,y) (1/50 .* (x.* cos(x/10) .* cos((x.^2)/100) - 5 .* sin(x/10) .* sin((x.^2)/100)));

% Analytical laplacian nabla u
nablaf =@(x,y) (1/2500 .* (-10.*x.*sin(x/10) .* cos(x.^2/100) - cos(x/10).*((x.^2+25) .* sin(x.^2/100) - 50.*cos(x.^2/100) ) ));

% Set X and Y vectors for plotting
X = reshape(grid(1,:), [N,M]); 
Y = reshape(grid(2,:), [N,M]);

% Different options for plotting...
figure(1);
subplot(2,2,1);
surf(X, Y, U);
title('Discrezied function u using a 50x20 grid.')
xlabel('x')
ylabel('y')


figure(2);
subplot(2,2,1);
surf(X,Y,Ux);
title('Discrezied derivative du/dx using a 50x20 grid.')
xlabel('x')
ylabel('y')

subplot(2,2,2);
surf(X,Y,dfx(X,Y));
title('Exact derivative du/dx.')
xlabel('x')
ylabel('y')

subplot(2,2,3);
surf(X,Y,abs(Ux-dfx(X,Y)));
title('Error of discretized derivative du/dx.')
xlabel('x')
ylabel('y')


figure(3);
subplot(2,2,1);
surf(X,Y,Uy);
title('Discrezied derivative du/dy using a 50x20 grid.')
axis([-10 5 0 3 0 2 0.8 1]);
xlabel('x')
ylabel('y')

subplot(2,2,2);
surf(X,Y,ones(N,M));
title('Exact derivative du/dy.')
axis([-10 5 0 3 0 2 0.8 1]);
xlabel('x')
ylabel('y')

subplot(2,2,3);
surf(X,Y,abs(Uy-1));
title('Error of discretized derivative du/dy.')
xlabel('x')
ylabel('y')

figure(4);
subplot(2,2,1);
surf(X,Y,Unabla);
title('Discretized laplacian of u using a 50x20 grid.')
xlabel('x')
ylabel('y')

subplot(2,2,2);
surf(X,Y,nablaf(X,Y));
title('Exact laplacian of u.')
xlabel('x')
ylabel('y')

subplot(2,2,3);
surf(X,Y,abs(Unabla-nablaf(X,Y)));
title('Error of discretized laplacian of u.')
xlabel('x')
ylabel('y')

figure(5);
t=-10:0.1:10;
subplot(2,2,1);
plot(t,fx(t), '-b');
title('Function u from -10 to 10 for y=0.')
xlabel('x')
ylabel('f(x)')

subplot(2,2,2);
surf(X,Y,Unabla-nablaf(X,Y));
title('Error of discretized laplacian of u for x=[-10,10] using a 50x20 grid.')
xlabel('x')
ylabel('y')


