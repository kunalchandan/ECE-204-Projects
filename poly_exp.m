## Copyright (C) 2020 Kunal Chandan
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see
## <https://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} poly_exp (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

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
