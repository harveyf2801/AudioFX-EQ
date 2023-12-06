%% Low Cut Band Class
% This function creates a low cut filter for an EQ.
%
% centerFreq:   Center frequency of the filter, where the cut off starts  
%               (can range from 1Hz to nyquist fs/2)
% q:            Quality factor, which determines the shape of the filter 
%               at the center frequency (q can range from 0.1 to 40)
% ̶d̶B̶g̶a̶i̶n̶ :      NOT NEEDED FOR CUT BANDS AND DEFAULT SET TO 0
% fs:           Sampling rate of the audio to apply the filter on

classdef LowCutBand < FilterBand

    methods
        function obj = LowCutBand(centerFreq, q, fs)
            %%LOW CUT BAND Constructor for the HighCutBand class.

            obj@FilterBand("Low Cut", centerFreq, q, 0, fs); % default setting the dBgain to 0
        end

        function [b, a] = calculateCoefficients(obj)
            %%CALCULATE COEFFICIENTS Outputs IIR coeffs b and a for a standard low cut filter band.
            
            % Intermediate variables
            w0 = 2 * pi * obj.centerFreq / obj.fs; % frequency in Hz to angular frequency conversion
            alpha = sin(w0) / (2 * obj.q); % calculating the q factor based on the angular frequency
            
            % Calculating the filter coefficients
            b0 = (1 + cos(w0))/2;
            b1 = -(1 + cos(w0));
            b2 = (1 + cos(w0))/2;
            a0 = 1 + alpha;
            a1 = -2*cos(w0);
            a2 = 1 - alpha;
        
            b = [b0, b1, b2];
            a = [a0, a1, a2];
        end
    end
end
