function PlotIIREQPhaseResponse(varargin)
    %PLOT IIR EQ PHASE RESPONSE A function to plot the phase response of an
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
        [phi, f] = phasez(b, a, n, fs); % getting the points to plot the phase response using the coeffs

        % Plot the response
        semilogx(f, rad2deg(phi), "DisplayName", varargin{band}.filterName); % converting radians to degrees
        hold on; % plotting all coeffs on the same graph

        % Convolve all coeffs for final response
        b_total = conv(b_total, b);
        a_total = conv(a_total, a);
    end
    
    % Plot the average filter phase response for all filter bands convolved
    [phi, f] = phasez(b_total, a_total, n, fs);
    semilogx(f, rad2deg(phi), "Color", "Red", "LineWidth", 1, "LineStyle", ":", "DisplayName", "All Filters");

    grid on; % turn grid on for the plot 
    hold off; % stopping the plotting on the same graph

    legend
    
    % Setting configurations for the figure
    figure(1)

    ylim([-360, 360]) % setting the y limits to be -360deg to 360deg
    xlim([20, 20000]) % setting the x limits to be 20Hz to 20kHz
    
    xticks([20, 50, 100, 200, 500, 1000, ...
        2000, 5000, 10000, 20000]); % setting the tick frequency number for the x axis
    xticklabels(["20", "50", "100", "200", "500", ...
        "1k", "2k", "5k", "10k", "20k"]); % setting the tick frequency labels for the x axis
    
    yticks([-360, -315, -270, -225, -180, -135, -90, -45, 0, ...
        45, 90, 135, 180, 225, 270, 315, 360]); % setting the tick degree number for the y axis
    yticklabels(["-360°", "-315°", "-270°", "-225°", "-180°", "-135°", "-90°", "-45°", "0", ...
        "45°", "90°", "135°", "180°", "225°", "270°", "315°", "360°"]); % setting the tick degree labels for the y axis

    xlabel('Frequency (Hz)') % setting the label for the x axis
    ylabel('Phase Shift (deg)') % setting the label for the y axis
    
    title("Phase Response")
end
