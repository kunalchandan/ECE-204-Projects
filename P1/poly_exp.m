## Copyright (C) 2020 Kunal Chandan
## 
## Author: Kunal Chandan <Kunal Chandan@KCHANDAN>
## Created: 2020-01-22

function retval = poly_exp (x)
  format long
   if (x < 0.0)
     retval =  1.0/poly_exp(-x);
     return;
   endif
   
   if (x > 1.0)
     retval = poly_exp(x/2) ^ 2;
     return;
   elseif (x <= 1.0)
      # x = [0, 0.25, 0.5, 0.75, 1];
      # y = exp(x)
      # p = polyfit(x,y,4)
      retval = ((((6.941567422026680e-02*x + 1.402760041417519e-01)*x + 5.097871380194817e-01)*x + 9.988030120775447e-01)*x + 1.0);
     return;
   endif
endfunction
