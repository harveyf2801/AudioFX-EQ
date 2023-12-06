function PlotIIREQPoleZero(varargin)
    %PLOT IIR EQ POLE ZERO A function to plot the pole zero of an
    % IIR filter, given a set of filter bands.
    %
    % If one filter band is provided, the function will plot the one band.
    % However, if more than one is provided, a summation of the filters
    % will be plotted.
    %                           ~ (varargin) ~
    % filter_bands: An array of IIR filter coefficients.

    % Setting the sampling n points for the plot to display
    n = 1024;
    
    b_total = 1;
    a_total = 1;
    
    % Go through each filter band and get the coeffs
    for band = 1:nargin

        [b, a] = varargin{band}.calculateCoefficients();

        % Convolve all coeffs for final response
        b_total = conv(b_total, b);
        a_total = conv(a_total, a);
    end

    [hw, fw] = zerophase(b_total, a_total, n, "whole"); % getting the points to plot the step response using the coeffs
        
    z = roots(b_total);
    p = roots(a_total);

    % Plot the response
    plot3(cos(fw), sin(fw), hw, "DisplayName", varargin{band}.filterName);

    hold on; % plotting all coeffs on the same graph

    plot3(cos(fw),sin(fw),zeros(size(fw)),'--')
    plot3(real(z),imag(z),zeros(size(z)),'o')
    plot3(real(p),imag(p),zeros(size(p)),'x')

    hold off;

    xlabel("Real") % setting the label for the x axis
    ylabel("Imaginary") % setting the label for the y axis
    view(35, 40)
    grid
    
    title("Pole Zero Plot")
end
