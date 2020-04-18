format long
sub1 = [0.3 -0.4 0.5];
dia1 = [1.3 1.7 1.9 2.5];
sup1 = [0.1 0.5 -0.6];
b1 = [5.2 -4.7 2.5 8.3]';
x1a = tri_solve( sub1, dia1, sup1, b1 )
A1 = diag( sub1, -1 ) + diag( dia1, 0 ) + diag( sup1, 1 );
x1b = A1\b1
norm( x1a - x1b ) % this should be small (1e-15), if not zero