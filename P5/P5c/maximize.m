function [x3] = maximize( f, x0, x1, x2, eps_step, eps_abs, max_iter )
  % Sort and gather sort indexes
  xs  =   [x0 x1 x2];
  fxs = f([x0 x1 x2]);
  [a i] = sortrows([fxs' xs'], [1]);
  fxs = a(:,1);
  xs  = a(:,2);
  
  % fit quadratic
  p = polyfit(xs, fxs, 2);
  [a b c] = num2cell(p){:};
  % find max of quadratic
  x3 = (-1*b)/(2*a);
  % check validity of arguments
  if f(x3) < f(xs(3))
    error( 'invalid arguments' );
  endif
  xs = shift(xs, -1);
  xs(3) = x3;
  
  count = 0;
  while 1
    if (abs(xs(3) - xs(2)) < eps_step) && (f(xs(3)) - f(xs(2)) < eps_abs)
      return;
    endif
    % fit quadratic
    p = polyfit(xs, fxs, 2);
    [a b c] = num2cell(p){:};
    
    x3 = (-1*b)/(2*a);
    xs = shift(xs, -1);
    xs(3) = x3;
    fxs = f(xs);
    count++;
    if count > max_iter
      error( 'method did not converge' );
    endif
  endwhile
end