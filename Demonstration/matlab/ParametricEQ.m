function [output_signal] = ParametricEQ(input_signal, varargin)
    %PARAMETRIC EQ Applies the filter bands to the input audio using TDF2
    %
    % input_signal:     the audio signal to apply the filters
    %                           ~ (varargin) ~
    % filter_bands:     the filter bands of base class type 'FilterBand',
    %                   to apply to the audio (dynamic / variable length
    %                   parameter)
    
    output_signal = input_signal;
    
    % Applying all of the filter bands to the input signal
    for band = 1:nargin-1
        [b, a] = varargin{band}.calculateCoefficients();
        [output_signal, ~] = TDF_II_Biquad(output_signal, b, a);
    end
end

