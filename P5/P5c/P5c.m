format long
maximize( @sin, 1, 1.5, 2, 1e-5, 1e-5, 10 )
maximize( @sin, 2, 2.5, 3, 1e-5, 1e-5, 10 )
##maximize( @sin, 3, 3.5, 4, 1e-5, 1e-5, 10 ) % invalid arguments
##maximize( @sin, 4, 4.5, 5, 1e-5, 1e-5, 10 ) % invalid arguments
##maximize( @sin, 5, 5.5, 6, 1e-5, 1e-5, 10 ) % invalid arguments
##maximize( @tanh, 0, 0.5, 1, 1e-5, 1e-5, 10 ) % method did not converge