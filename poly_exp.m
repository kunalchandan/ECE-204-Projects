## Copyright (C) 2020 Kunal Chandan
## 
## Author: Kunal Chandan <Kunal Chandan@KCHANDAN>
## Created: 2020-01-22

function retval = poly_exp (x)
   if (x < 0.0)
     retval =  1.0/poly_exp(-x);
     return;
   endif
   
   if (x > 1.0)
     retval = poly_exp(x/2) ^ 2;
     return;
   elseif (x < 1.0)
     retval = inter_poly(x);
     return;
   endif
endfunction
