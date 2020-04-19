u10 = @(x)(1.0);
u1a = @(t)(0.0);
u1b = @(t)(7.0);
%% Test 1
U = crank_nicolson( 3.0, 0.0, 12.0, 0.0, u10, u1a, u1b, 6, 0.4, 4 );

data = dlmread('t1.txt', ' ', 0, 0);
norm(U - data)
%% Test 2
zero = @(t)(0.0);
U = crank_nicolson( 0.5, 0, pi, 0, @sin, zero, zero, 10, 0.5, 4 );

data = dlmread('t2.txt', ' ', 0, 0);
norm(U - data)
%% Test 3
u20 = @(x)(sin(pi*x));
u2a = @(t)( 3.0*(1.0 - exp( -t )));
u2b = @(t)(-2.0*(1.0 - exp( -t )));
U = crank_nicolson( 2.5, 0, 1.0, 0, u20, u2a, u2b, 5, 0.1, 8 );

data = dlmread('t3.txt', ' ', 0, 0);
norm(U - data)