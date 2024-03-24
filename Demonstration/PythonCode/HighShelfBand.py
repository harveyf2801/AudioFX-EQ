import numpy as np
from PythonCode.FilterBand import FilterBand

class HighShelfBand(FilterBand):
    """
    High Shelf Band Class for creating a high shelf filter for an EQ.
    """
    def __init__(self, centerFreq, dBgain, q, fs):
        """
        Constructor for the HighShelfBand class.

        Parameters:
        - centerFreq: Center frequency of the filter, where the shelf starts
                      (can range from 1Hz to nyquist fs/2)
        - dBgain: Gain at the center frequency (in decibels)
        - q: Quality factor, which determines the shape of the filter
               at the center frequency (q can range from 0.1 to 40)
        - fs: Sampling rate of the audio to apply the filter on
        """
        super().__init__("High Shelf", centerFreq, q, dBgain, fs)

    def calculate_coefficients(self):
        """
        CALCULATE COEFFICIENTS Outputs IIR coeffs b and a for a standard high shelf filter band.
        """
        # Intermediate variables
        w0 = 2 * np.pi * self.centerFreq / self.fs  # frequency in Hz to angular frequency conversion
        alpha = np.sin(w0) / (2 * self.q)  # calculating the q factor based on the angular frequency
        A = 10 ** (self.dBgain / 40)  # converting decibel gain into 0.0 to 1.0

        # Calculating the filter coefficients
        b0 = A * ((A + 1) + (A - 1) * np.cos(w0) + 2 * np.sqrt(A) * alpha)
        b1 = -2 * A * ((A - 1) + (A + 1) * np.cos(w0))
        b2 = A * ((A + 1) + (A - 1) * np.cos(w0) - 2 * np.sqrt(A) * alpha)
        a0 = (A + 1) - (A - 1) * np.cos(w0) + 2 * np.sqrt(A) * alpha
        a1 = 2 * ((A - 1) - (A + 1) * np.cos(w0))
        a2 = (A + 1) - (A - 1) * np.cos(w0) - 2 * np.sqrt(A) * alpha

        b = [b0, b1, b2]
        a = [a0, a1, a2]

        return b, a
