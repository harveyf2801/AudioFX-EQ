%% Peaking Band Class
% This function creates a peaking filter band for an EQ.
%
% centerFreq:   Center frequency of the peaking filter
%               (can range from 1Hz to nyquist fs/2)
% q:            Quality factor, which determines the shape of the filter 
%               at the center frequency (q can range from 0.1 to 40)
% dBgain:       Gain at the center frequency (in decibels)
% fs:           Sampling rate of the audio to apply the filter on

classdef PeakingBand < FilterBand

    methods
        function obj = PeakingBand(centerFreq, dBgain, q, fs)
            %%PEAKING BAND Constructor for the PeakingBand class.

            obj@FilterBand("Peaking", centerFreq, q, dBgain, fs);
        end

        function [b, a] = calculateCoefficients(obj)
            %%CALCULATE COEFFICIENTS Outputs IIR coeffs b and a for a standard peaking filter band.
            
            % Intermediate variables
            w0 = 2 * pi * obj.centerFreq / obj.fs; % frequency in Hz to angular frequency conversion
            alpha = sin(w0) / (2 * obj.q); % calculating the q factor based on the angular frequency
            A = 10 ^ (obj.dBgain / 40); % converting decibel gain into 0.0 to 1.0
            
            % Calculating the filter coefficients
            b0 =   1 + alpha * A;
            b1 =  -2 * cos(w0);
            b2 =   1 - alpha * A;
            a0 =   1 + alpha / A;
            a1 =  -2 * cos(w0);
            a2 =   1 - alpha / A;

            b = [b0, b1, b2];
            a = [a0, a1, a2];
        end
    end
end