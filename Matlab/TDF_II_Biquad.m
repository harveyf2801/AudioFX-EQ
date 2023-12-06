function [Y, zi] = TDF_II_Biquad(X, b, a, zi)
    %%TDF II BIQUAD A function which uses Transposed Direct Form II to
    % apply a biquad filter to an input signal.
    % Returning the filtered output signal and zi (the initial
    % conditions to use on the next block of related audio).
    %
    % Using Fontaine, et al. (2011) equation for TDF2 structure
    %
    % X: input signal
    % b, a: biquad coefficients
    % zi: an an initial condition for filter delays

    % Make sure coeffs a and b are equal in size (padding with zeros)
    len_a = length(a);
    n  = length(b);

    if len_a > n
        n = len_a;
        b(n) = 0; % padding with zero coefficients for 'b' if 'a' is longer
    elseif len_a < n
        a(n) = 0; % padding with zero coefficients for 'a' if 'b' is longer
    end
    
    % Allocates 0's for zi if omited
    zi(n) = 0;
    
    % Normalise a and b coefficients
    b = b / a(1);
    a = a / a(1);
    
    % Allocates 0's for Y output
    Y = zeros(size(X));

    % Checking the filter coeffs are for an IIR filter
    if len_a > 1
        
        % Applying the TDF2 filter structure
        for s = 1:length(Y)

            % Initialise the filtered output 'Y' for the current sample
            % using the feedforward coefficient 'b(1)' and initial state 'zi(1)'
            Y(s) = b(1) * X(s) + zi(1);

            % Loop through the filter coefficients and state values (except the last element)
            for i = 2:n-1

                % Update the state values ('zi') recursively based on input
                % 'X', current state, and filter coefficients 'a' and 'b'
                zi(i - 1) = b(i) * X(s) + zi(i) - a(i) * Y(s);
            end

            % Omitting zi(n) which is set to 0 and update the last state
            % value ('zi(n-1)') for the current sample
            zi(n - 1) = b(n) * X(s) - a(n) * Y(s);
        end

    else
        error("This function only performs IIR filters, not FIR");
    end
       
    % Remove the last element in 'zi' as it's always 0
    zi = zi(1:n - 1);
end