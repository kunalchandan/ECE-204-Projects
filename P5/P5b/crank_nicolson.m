function [U] = crank_nicolson( kappa, a, b, t0, u0, ua, ub, nx, delta_t, nt )
  
  % There might be something off about the b index
  U = zeros(nx+1, nt+1);
  h = (a + b)/nx;
  c = delta_t*kappa/h/h;
  % 1.
  for k = 0:nx
    U(k+1,1) = u0(a + h*k);
  endfor
  % 2.
  for L = 2:(nt+1)
    t = t0 + delta_t*L;
    % a.
    U(  1 ,L) = ua(t);
    U(nx+1,L) = ub(t);
    % b.
    l = L-1;
    % build the solution vector
    b = zeros(nx-1, 1);
    for i = 1:(nx-1)
      if i == 1
        b(i) = c*U(i,l) + 2*(1-c)*U(i+1,l) + c*U(i+2,l) + c*ua(t+delta_t);
      elseif i == (nx-1)
        b(i) = c*U(i,l) + 2*(1-c)*U(i+1,l) + c*U(i+2,l) + c*ub(t+delta_t);
      else
        b(i) = c*U(i,l) + 2*(1-c)*U(i+1,l) + c*U(i+2,l);
      endif
    endfor
    % build the coeffs matrix
    A = zeros(nx-1, nx-1);
    A = A + (diag(2*(c+1)*ones(nx-1, 1), 0)); % center
    A = A + (diag(-1*c*ones(nx-2, 1), 1)); % super
    A = A + (diag(-1*c*ones(nx-2, 1),-1)); % sub
    
    % I suppose to solve this linear system you can elect to use the tri-solve
    % from project 5a, however since I suppose that is not the focus of this 
    % project I will use the builtin solver
    U(2:(nx), L) = (A\b);
  endfor
  
end
