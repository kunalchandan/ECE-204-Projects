a0 = poly_exp(3);
a1 = e^3;

A = [5 0.3 -0.2; 0.3 6 0.1; -0.2 0.1 7];
b = [1 2 3]';
v = A \ b;
A*v;
iter_solve(A, b, 20, 1e-12)