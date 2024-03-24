import numpy as np

def TDF_II_Biquad(X, b, a):
    """
    TDF II BIQUAD A function which uses Transposed Direct Form II to
    apply a biquad filter to an input signal.
    Returning the filtered output signal.

    Parameters:
    - X: input signal
    - b: biquad feedforward coefficients
    - a: biquad feedback coefficients

    Returns:
    - Y: filtered output signal
    """

    # Allocating memory for filter output
    out = [0.0] * len(X)

    # Applying the TDF2 filter structure
    for i in range(len(X)):
        tmp = 0.0

        for j in range(len(b)):
            if i - j < 0:
                continue
            tmp += b[j] * X[i - j]

        for j in range(1, len(a)):
            if i - j < 0:
                continue
            tmp -= a[j] * out[i - j]

        tmp /= a[0]
        out[i] = tmp

    return out