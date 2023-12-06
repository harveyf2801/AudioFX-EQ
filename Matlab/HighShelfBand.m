%% High Shelf Band Class
% This function creates a high shelf filter for an EQ.
%
% centerFreq:   Center frequency of the filter, where the shelf starts 
%               (can range from 1Hz to nyquist fs/2)
% q:            Quality factor, which determines the shape of the filter 
%               at the center frequency (q can range from 0.1 to 40)
% dBgain:       Gain at the center frequency (in decibels)
% fs:           Sampling rate of the audio to apply the filter on

classdef HighShelfBand < FilterBand

    methods
        function obj = HighShelfBand(centerFreq, dBgain, q, fs)
            %%HIGH SHELF BAND Constructor for the HighShelfBand class.

            obj@FilterBand("High Shelf", centerFreq, q, dBgain, fs);
        end

        function [b, a] = calculateCoefficients(obj)
            %%CALCULATE COEFFICIENTS Outputs IIR coeffs b and a for a standard high shelf filter band.
            
            % Intermediate variables
            w0 = 2 * pi * obj.centerFreq / obj.fs; % frequency in Hz to angular frequency conversion
            alpha = sin(w0) / (2 * obj.q); % calculating the q factor based on the angular frequency
            A = 10 ^ (obj.dBgain / 40); % converting decibel gain into 0.0 to 1.0

            % Calculating the filter coefficients
            b0 = A*( (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha);
            b1 = -2*A*( (A-1) + (A+1)*cos(w0));
            b2 = A*( (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha);
            a0 = (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha;
            a1 = 2*( (A-1) - (A+1)*cos(w0));
            a2 = (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha;
        
            b = [b0, b1, b2];
            a = [a0, a1, a2];
        end
    end
end
