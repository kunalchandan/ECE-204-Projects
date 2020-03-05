classdef InterpolatingData < handle
    % The properties are the member variables of the class
    % - they are not typed
    properties
        Data;
        Head;
        Integral;
        Delta_t;
    end
    methods
        % The constructor
        function obj = InterpolatingData( dt, init )
            % create a vector of length 3 with all entries equal to 'init'
            % - ones( m, n ) creates an m x n matrix with entries equal to '1'
            obj.Data = init*ones( 3, 1 );
            % set the head index to '1'
            obj.Head = 1;
            obj.Integral = 0.0;
            obj.Delta_t = dt;
        end
        function [] = add( obj, val )
            % Decrement the head index, but cycling it back to 3 if it drops to 0
            obj.Head = mod1( obj.Head - 1, 3 );
            % Store the new entry at that index
            obj.Data(obj.Head) = val;
            % Half-Simpson's rule
            obj.Integral = obj.Integral + ( ...
                5.0*obj.Data( obj.Head) + ...
                + 8.0*obj.Data(mod1( obj.Head + 1, 3 )) ...
                - obj.Data(mod1( obj.Head + 2, 3 )) ...
                )/12.0*obj.Delta_t;
        end
        % Return the most recent value
        function [y] = current( obj )
            y = obj.Data(obj.Head);
        end
        % Return the interpolating polynomial through the last three points evaluated
        % at one time step into the future
        function [y] = next( obj )
            y = 3.0*obj.Data(obj.Head) ...
                - 3.0*obj.Data(mod1( obj.Head + 1, 3 )) ...
                + obj.Data(mod1( obj.Head + 2, 3 ));
        end
        % Return the derivative of the interpolating polynomial through the last three
        % points evaluated at the current time step
        function [y] = diff( obj )
            y = ( 3.*obj.Data(obj.Head) ...
                - 4.*obj.Data(mod1( obj.Head + 1, 3 )) ...
                + obj.Data(mod1( obj.Head + 2, 3 )) )/(2.0*obj.Delta_t);
        end
        % Return the second derivative of the interpolating polynomial through the last
        % three points evaluated at the current time step
        function [y] = diff2( obj )
            y = ( obj.Data(obj.Head) ...
                - 2.*obj.Data(mod1( obj.Head + 1, 3 )) ...
                + obj.Data(mod1( obj.Head + 2, 3 )) )/obj.Delta_t^2;
        end
        % Return the property 'Integral'
        function [y] = int( obj )
            y = obj.Integral;
        end
    end
end
function r = mod1( m, n )
r = mod( m + n - 1, n ) + 1;
end