## Copyright (C) 2020 Kunal Chandan
## 
## Author: Kunal Chandan <Kunal Chandan@KCHANDAN>
## Created: 2020-01-22

function [v] = iter_solve (A, b, N_max, eps_step)
  format long
  A_diag = diag(diag(A))
  A_off = A - A_diag;
  v = inv(A_diag) * b;
  v_n = v;
  for i = 1:N_max
    v = v_n;
    v_n = (inv(A_diag) * b) - (inv(A_diag) * A_off * v)
  endfor
  if (norm(v_n - v) > eps_step)
    error 'the method did not converge';
  endif
  retval = v_n
endfunction
