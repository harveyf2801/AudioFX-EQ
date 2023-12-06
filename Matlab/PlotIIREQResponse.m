function PlotIIREQResponse(varargin)
    %PLOT IIR EQ RESPONSE A function to plot the magnitude response of an
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
        [h, f] = freqz(b, a, n, fs); % getting the points to plot the response using the coeffs

        % Plot the response
        area(f, mag2db(abs(h)), "FaceAlpha", 0.5, "DisplayName", varargin{band}.filterName); % converting magnitude to decibels
        hold on; % plotting all coeffs on the same graph

        % Convolve all coeffs for final response
        b_total = conv(b_total, b);
        a_total = conv(a_total, a);
    end
    
    % Plot the average filter response for all filter bands convolved
    [h, f] = freqz(b_total, a_total, n, fs);
    plot(f, mag2db(abs(h)), "Color", "Red", "LineWidth", 1, "LineStyle", ":", "DisplayName", "All Filters");

    grid on; % turn grid on for the plot 
    hold off; % stopping the plotting on the same graph

    legend;
    
    % Setting configurations for the figure
    figure(1)

    set(gca, 'XScale', 'log') % set the x axis as logarithmic

    ylim([-40, 10]) % setting the y limits to be -40dB to 10dB
    xlim([20, 20000]) % setting the x limits to be 20Hz to 20kHz
    
    xticks([20, 50, 100, 200, 500, 1000, ...
        2000, 5000, 10000, 20000]); % setting the tick frequency number for the x axis
    xticklabels(["20", "50", "100", "200", "500", ...
        "1k", "2k", "5k", "10k", "20k"]); % setting the tick frequency labels for the x axis

    xlabel('Frequency (Hz)') % setting the label for the x axis
    ylabel('Magnitude (dB)') % setting the label for the y axis

    title("Magnitude Response")

end