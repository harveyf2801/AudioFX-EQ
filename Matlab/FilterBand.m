%% Filter Band Base Class
% A base class to create a filter band for an audio EQ.

classdef FilterBand

    properties
        filterName  % Name of the filter band
        centerFreq  % Center frequency of the filter (can range from 1Hz to nyquist fs/2)
        q           % Quality factor, which determines the shape of the filter at the center frequency (q can range from 0.1 to 40)
        dBgain      % Gain at the center frequency (in decibels)
        fs          % Sampling rate of the audio to apply the filter on
    end
    
    methods
        function obj = FilterBand(filterName, centerFreq, q, dBgain, fs)
            %%FILTER BAND Constructor for the FilterBand class.
            
            obj.filterName = filterName;
            obj.centerFreq = centerFreq;
            obj.q = q;
            obj.dBgain = dBgain;
            obj.fs = fs;
        end
    end
end