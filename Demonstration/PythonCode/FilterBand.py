class FilterBand:
    """
    Filter Band Base Class for an audio EQ.
    """
    def __init__(self, filterName, centerFreq, q, dBgain, fs):
        """
        Constructor for the FilterBand class.

        Parameters:
        - filterName: Name of the filter band
        - centerFreq: Center frequency of the filter (can range from 1Hz to nyquist fs/2)
        - q: Quality factor, which determines the shape of the filter at the center frequency (q can range from 0.1 to 40)
        - dBgain: Gain at the center frequency (in decibels)
        - fs: Sampling rate of the audio to apply the filter on
        """
        self.filterName = filterName
        self.centerFreq = centerFreq
        self.q = q
        self.dBgain = dBgain
        self.fs = fs
