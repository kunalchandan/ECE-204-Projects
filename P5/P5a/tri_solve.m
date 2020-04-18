function [sol] = tri_solve( sub, dia, sup, b )
  % assert all arguments are vectors
  if ~isequal(1, min(size(sub)), min(size(dia)), min(size(sup)), min(size(b)))
    error( 'all arguments must be vectors');
  endif
  % assert all arguments matching dimensions
  if ~(isequal(max(size(dia)), max(size(b  )))  && ...
       isequal(max(size(sub)), max(size(sup)))) || ...
     ~(isequal(max(size(b))-1, max(size(sup))))
    error( 'non-matching dimensions' );
  endif
  n = max(size(dia));
  for i = 1:n
    % Check rows
    if ( ((i == 1)   &&   (abs(dia(i)) < (abs(sup( i ))))) || ...
         ((i == n)   &&   (abs(dia(i)) < (abs(sub(i-1))))) || ...
         ((i~=n)&&(i~=1)&&(abs(dia(i)) < (abs(sub(i-1)) + abs(sup(i))))))
         
        error( 'the matrix is not diagonally dominant' );
    endif
    % Check columns (swap sup with sub)
    if ( ((i == 1)   &&   (abs(dia(i))  <  (abs(sub( i ))))) || ...
         ((i == n)   &&   (abs(dia(i))  <  (abs(sup(i-1))))) || ...
         ((i~=n)&&(i~=1)&&(abs(dia(i))  <  (abs(sup(i-1)) + abs(sub(i))))))
        error( 'the matrix is not diagonally dominant' );
    endif
  endfor
  
  %% Gaussian Elimination
  for k = 1:(n - 1)
    dia(k+1) = dia(k+1) - (sup(k)*sub(k)/dia(k));
    
    b(k+1) = b(k+1) - (b(k)*sub(k)/dia(k));
    % We can assume sub all becomes 0, 
    % we don't actually need to compute the subtraction  
  endfor
  
  sol = zeros(n, 1);
  sol(n) = b(n)/dia(n);
  for k = (n-1):-1:1
    sol(k) = (b(k) - (sup(k)*sol(k+1)))/dia(k);
  endfor
endfunction
