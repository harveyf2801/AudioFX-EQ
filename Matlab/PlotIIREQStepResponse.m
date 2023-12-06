function PlotIIREQStepResponse(varargin)
    %PLOT IIR EQ STEP RESPONSE A function to plot the step response of an
    % IIR filter, given a set of filter bands.
    %
    %                           ~ (varargin) ~
    % filter_bands: An array of IIR filter coefficients.

    % Setting the sampling n points for the plot to display
    n = 2048;
    
    b_total = 1;
    a_total = 1;
    
    % Go through each filter band and get the coeffs
    for band = 1:nargin
        fs = varargin{band}.fs;

        [b, a] = varargin{band}.calculateCoefficients();
        [h, t] = stepz(b, a, n, fs); % getting the points to plot the step response using the coeffs

        % Plot the response
        plot(t, h, "DisplayName", varargin{band}.filterName);
        hold on; % plotting all coeffs on the same graph

        % Convolve all coeffs for final response
        b_total = conv(b_total, b);
        a_total = conv(a_total, a);
    end
    
    % Plot the average filter step response for all filter bands convolved
    [h, t] = stepz(b_total, a_total, n, fs);
    plot(t, h, "Color", "Red", "LineWidth", 1, "LineStyle", ":", "DisplayName", "All Filters");

    hold off; % stopping the plotting on the same graph

    legend
    
    % Setting configurations for the figure
    figure(1)

    xlabel('Samples (n)') % setting the label for the x axis
    ylabel('Amplitude (V)') % setting the label for the y axis
    
    title("Step Response")
end
