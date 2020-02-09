LogicalStr = {'false', 'true'};

for i = [0.0 0.001 0.005 0.01 0.05 0.1]
    disp(i)
    interp = InterpolatingData( 0.1, 2.0 );
    least = LeastSquaresData( 0.1, 2.0 );
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % This is the only value you will be changing. %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    error_amount = i;
    sample_rate = 10; % 10 Hz
    dt = 1/sample_rate; % 0.1 s
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % You will set this to 100 when running your tests. %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    N = 100;
    % Define four functions inline:
    % - the actual function, the first and second derivatives,
    % and the integral. These can be called using y(3.2),
    % dy(3.2), d2y(3.2) and inty(3.2), respectively.
    y = @(t)( 2.0 + sin( t ));
    dy = @(t)( cos( t ));
    d2y = @(t)( -sin( t ));
    inty = @(t)(1.0 + 2.0*t - cos( t ));
    vals_interp = zeros( N, 1 );
    nexts_interp = zeros( N, 1 );
    diffs_interp = zeros( N, 1 );
    diff2s_interp = zeros( N, 1 );
    ints_interp = zeros( N, 1 );
    vals_least = zeros( N, 1 );
    nexts_least = zeros( N, 1 );
    diffs_least = zeros( N, 1 );
    diff2s_least = zeros( N, 1 );
    ints_least = zeros( N, 1 );
    vals_exact = zeros( N, 1 );
    errs_exact = zeros( N, 1 );
    nexts_exact = zeros( N, 1 );
    diffs_exact = zeros( N, 1 );
    diff2s_exact = zeros( N, 1 );
    ints_exact = zeros( N, 1 );
    for i = 1:N
        t = i*dt;
        err = randn( 1, 1 );
        interp.add( y( t ) + error_amount*err );
        least.add( y( t ) + error_amount*err );
        vals_interp(i) = interp.current();
        nexts_interp(i) = interp.next();
        diffs_interp(i) = interp.diff();
        diff2s_interp(i) = interp.diff2();
        ints_interp(i) = interp.int();
        vals_least(i) = least.current();
        nexts_least(i) = least.next();
        diffs_least(i) = least.diff();
        diff2s_least(i) = least.diff2();
        ints_least(i) = least.int();
        vals_exact(i) = y( t );
        errs_exact(i) = error_amount*err;
        nexts_exact(i) = y( t + dt );
        diffs_exact(i) = dy( t );
        diff2s_exact(i) = d2y( t );
        ints_exact(i) = inty( t );
    end
    disp( 'Current values' );
    [vals_interp vals_least vals_exact errs_exact];
    norm( vals_interp - vals_exact );
    norm( vals_least - vals_exact );
    disp(LogicalStr{(norm( vals_interp - vals_exact ) < norm( vals_least - vals_exact )) + 1});
    
    disp( 'Next values' );
    [nexts_interp nexts_least nexts_exact];
    norm( nexts_interp - nexts_exact );
    norm( nexts_least - nexts_exact );
    disp(LogicalStr{(norm( nexts_interp - nexts_exact ) < norm( nexts_least - nexts_exact )) + 1});
    
    disp( 'Derivatives' );
    [diffs_interp diffs_least diffs_exact];
    norm( diffs_interp - diffs_exact );
    norm( diffs_least - diffs_exact );
    disp(LogicalStr{(norm( diffs_interp - diffs_exact ) < norm( diffs_least - diffs_exact )) + 1});

    disp( 'Second derivatives' );
    [diff2s_interp diff2s_least diff2s_exact];
    norm( diff2s_interp - diff2s_exact );
    norm( diff2s_least - diff2s_exact );
    disp(LogicalStr{(norm( diff2s_interp - diff2s_exact ) < norm( diff2s_least - diff2s_exact )) + 1});

    disp( 'Integrals' );
    [ints_interp ints_least ints_exact];
    norm( ints_interp - ints_exact );
    norm( ints_least - ints_exact );
    disp(LogicalStr{(norm( ints_interp - ints_exact ) < norm( ints_least - ints_exact )) + 1});
end