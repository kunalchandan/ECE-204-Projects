function [fx] = concave_interp( x1, f1, df1, d2f1, x2, f2, df2, d2f2, x )
  if x1 == x2
    error( 'the end points must differ' );
  end
  A = [[    x1^5     x1^4     x1^3   x1^2   x1^1 1];
       [  5*x1^4   4*x1^3   3*x1^2 2*x1^1   1    0];
       [5*4*x1^3 4*3*x1^2 3*2*x1^1 2        0    0];
       [    x2^5     x2^4     x2^3   x2^2   x2^1 1];
       [  5*x2^4   4*x2^3   3*x2^2 2*x2^1   1    0];
       [5*4*x2^3 4*3*x2^2 3*2*x2^1 2        0    0]];
  b = [f1 df1 d2f1 f2 df2 d2f2]';
  as = A\b;
  fx = polyval(as, x);
  
end
