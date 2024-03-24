import numpy as np
from PythonCode.FilterBand import FilterBand

class LowCutBand(FilterBand):
    """
    Low Cut Band Class for creating a low cut filter for an EQ.
    """
    def __init__(self, centerFreq, q, fs):
        """
        Constructor for the LowCutBand class.

        Parameters:
        - centerFreq: Center frequency of the filter, where the cut off starts
                      (can range from 1Hz to nyquist fs/2)
        - q: Quality factor, which determines the shape of the filter
               at the center frequency (q can range from 0.1 to 40)
        - fs: Sampling rate of the audio to apply the filter on
        """
        super().__init__("Low Cut", centerFreq, q, 0, fs)  # Default setting the dBgain to 0

    def calculate_coefficients(self):
        """
        CALCULATE COEFFICIENTS Outputs IIR coeffs b and a for a standard low cut filter band.
        """
        # Intermediate variables
        w0 = 2 * np.pi * self.centerFreq / self.fs  # frequency in Hz to angular frequency conversion
        alpha = np.sin(w0) / (2 * self.q)  # calculating the q factor based on the angular frequency

        # Calculating the filter coefficients
        b0 = (1 + np.cos(w0)) / 2
        b1 = -(1 + np.cos(w0))
        b2 = (1 + np.cos(w0)) / 2
        a0 = 1 + alpha
        a1 = -2 * np.cos(w0)
        a2 = 1 - alpha

        b = [b0, b1, b2]
        a = [a0, a1, a2]

        return b, a
