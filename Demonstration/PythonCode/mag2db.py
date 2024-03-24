import numpy as np

def mag2db(magnitude):
    """
    Convert magnitude to decibels (dB).

    Parameters:
    - magnitude: The magnitude value.

    Returns:
    - The magnitude converted to decibels.
    """
    return 20 * np.log10(magnitude)