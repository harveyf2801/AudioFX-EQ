%% Notch Band Class
% This function creates a notch band filter for an EQ.
%
% centerFreq:   Center frequency of the notch filter
% q:            Quality factor, which determines the shape of the filter 
%               at the center frequency (q can range from 0.1 to 40)
% ̶d̶B̶g̶a̶i̶n̶ :      NOT NEEDED FOR NOTCH BANDS AND DEFAULT SET TO -INF
% fs:           Sampling rate of the audio to apply the filter on

classdef NotchBand < FilterBand

    methods
        function obj = NotchBand(centerFreq, q, fs)
            %%NOTCH BAND Constructor for the NotchBand class.

            obj@FilterBand("Notch", centerFreq, q, -inf, fs); % default setting the dBgain to -inf
        end

        function [b, a] = calculateCoefficients(obj)
            %%CALCULATE COEFFICIENTS Outputs IIR coeffs b and a for a standard notch filter band.
            
            % Intermediate variables
            w0 = 2 * pi * obj.centerFreq / obj.fs; % frequency in Hz to angular frequency conversion
            alpha = sin(w0) / (2 * obj.q); % calculating the q factor based on the angular frequency
            
            % Calculating the filter coefficients
            b0 = 1;
            b1 = -2*cos(w0);
            b2 = 1;
            a0 = 1 + alpha;
            a1 = -2*cos(w0);
            a2 = 1 - alpha;
        
            b = [b0, b1, b2];
            a = [a0, a1, a2];
        end
    end
end