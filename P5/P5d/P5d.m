format long
% 2
% d d
% f(1) = 1 -- f(1) = 0 --- f(1) = 0
% dx 2
% dx
% 2
% d d
% f(2) = 2 -- f(2) = 0 --- f(2) = 0
% dx 2
% dx
%
% The for loop runs x from 1 to 2 in steps of 0.1, so in other
% words, x takes on the values 0, 0.1, 0.2, 0.3, ..., 0.8, 0.9, 1
for x = 1:0.1:2
 concave_interp( 1, 1, 0, 0, 2, 2, 0, 0, x )
end
% 2
% d d
% f(1) = 1.1 -- f(1) = -0.1 --- f(1) = -0.4
% dx 2
% dx
% 2
% d d
% f(2) = 2.2 -- f(2) = 0.2 --- f(2) = 0.3
% dx 2
% dx
%
% The for loop runs x from 1 to 2 in steps of 0.1, so in other
% words, x takes on the values 0, 0.1, 0.2, 0.3, ..., 0.8, 0.9, 1
for x = 1:0.1:2
 concave_interp( 1, 1.1, -0.1, -0.4, 2, 2.2, 0.2, 0.3, x )
end