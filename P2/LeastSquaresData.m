classdef LeastSquaresData < handle
  properties
    Head;
    Data;
    Integral;
    Delta_t;
  end
  methods
    function obj = LeastSquaresData( dt, init )
      obj.Head = 1;
      obj.Data = init*ones( 5, 1 );
      obj.Integral = 0.0;
      obj.Delta_t = dt;
    end
    function [] = add( obj, val )
      % Enter your implementation here
    end
    function [y] = current( obj )
      % Enter your implementation here
      y = 0.0;
    end
    function [y] = next( obj )
      % Enter your implementation here
      y = 0.0;
    end
    function [y] = diff( obj )
      % Enter your implementation here
      y = 0.0;
    end
    function [y] = diff2( obj )
      % Enter your implementation here
      y = 0.0;
    end
    function [y] = int( obj )
    % This is done for you...
    y = obj.Integral;
    end
  end
end
function r = mod1( m, n )
 r = mod( m + n - 1, n ) + 1;
end