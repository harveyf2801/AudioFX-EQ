from PythonCode.TDF_II_Biquad import TDF_II_Biquad

def ParametricEQ(input_signal, *filter_bands):
    """
    PARAMETRIC EQ Applies the filter bands to the input audio using TDF2

    Parameters:
    - input_signal: the audio signal to apply the filters
    - *filter_bands: the filter bands of base class type 'FilterBand',
                      to apply to the audio (dynamic / variable length parameter)
    """
    output_signal = input_signal.copy()

    # Applying all of the filter bands to the input signal
    for band in filter_bands:
        b, a = band.calculate_coefficients()
        output_signal = TDF_II_Biquad(output_signal, b, a)

    return output_signal
