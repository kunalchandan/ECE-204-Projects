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
## @deftypefn {} {@var{retval} =} inter_poly (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Kunal Chandan <Kunal Chandan@KCHANDAN>
## Created: 2020-01-22

function retval = inter_poly (x)
  # x = [0, 0.25, 0.5, 0.75, 1];
  # y = exp(x)
  # p = polyfit(x,y,4)
  retval = ((((6.941567422026680e-02*x + 1.402760041417519e-01)*x + 5.097871380194817e-01)*x + 9.988030120775447e-01)*x + 1.000000);
  return;
endfunction
