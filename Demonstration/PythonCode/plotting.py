import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import freqz, zpk2tf, tf2zpk, lfilter
from PythonCode.mag2db import mag2db

def PlotIIREQResponse(*args):
    """
    PLOT IIR EQ RESPONSE A function to plot the magnitude response of an
    IIR filter, given a set of filter bands.

    Parameters:
    - *args: An array of IIR filter coefficients.
    """
    # Setting the sampling n points for the plot to display
    n = 2048

    b_total = 1
    a_total = 1

    # Go through each filter band and get the coeffs
    for band in args:
        fs = band.fs

        b, a = band.calculate_coefficients()
        w, h = freqz(b, a, n, fs=fs)  # getting the points to plot the response using the coeffs

        # Plot the response
        plt.fill_between(w, mag2db(np.abs(h)), alpha=0.5, label=band.filterName)  # converting magnitude to decibels
        # plt.hold(True)  # plotting all coeffs on the same graph

        # Convolve all coeffs for final response
        b_total = np.convolve(b_total, b)
        a_total = np.convolve(a_total, a)

    # Plot the average filter response for all filter bands convolved
    w, h = freqz(b_total, a_total, n, fs=fs)
    plt.plot(w, mag2db(np.abs(h)), 'r:', linewidth=1, label='All Filters')

    plt.grid(True)  # turn grid on for the plot
    # plt.hold(False)  # stopping the plotting on the same graph

    plt.legend()

    # Setting configurations for the figure
    plt.figure(1)

    plt.xscale('log')  # set the x axis as logarithmic

    plt.ylim([-40, 10])  # setting the y limits to be -40dB to 10dB
    plt.xlim([20, 20000])  # setting the x limits to be 20Hz to 20kHz

    plt.xticks([20, 50, 100, 200, 500, 1000,
                2000, 5000, 10000, 20000],  # setting the tick frequency number for the x axis
               ["20", "50", "100", "200", "500",
                "1k", "2k", "5k", "10k", "20k"])  # setting the tick frequency labels for the x axis

    plt.xlabel('Frequency (Hz)')  # setting the label for the x axis
    plt.ylabel('Magnitude (dB)')  # setting the label for the y axis

    plt.title("Magnitude Response")
    plt.show()


def PlotIIREQPoleZero(*filter_bands):
    """
    PLOT IIR EQ POLE ZERO A function to plot the pole zero of an
    IIR filter, given a set of filter bands.

    If one filter band is provided, the function will plot the one band.
    However, if more than one is provided, a summation of the filters
    will be plotted.

    Parameters:
    - filter_bands: An array of IIR filter coefficients.
    """

    # Setting the sampling n points for the plot to display
    n = 1024

    b_total = 1
    a_total = 1

    # Go through each filter band and get the coeffs
    for band in filter_bands:
        b, a = band.calculate_coefficients()

        # Convolve all coeffs for final response
        b_total = np.convolve(b_total, b)
        a_total = np.convolve(a_total, a)

    # Calculate the step response
    _, hw = freqz(b_total, a_total, n, whole=True)

    # Calculate the pole-zero locations
    z, p, _ = tf2zpk(b_total, a_total)

    # Plot the pole-zero plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Plot the step response
    fw = np.linspace(0, 2*np.pi, n)
    ax.plot3D(np.cos(fw), np.sin(fw), np.abs(hw), label="Step Response")

    # Plot the unit circle
    ax.plot3D(np.cos(fw), np.sin(fw), np.zeros_like(fw), '--', label="Unit Circle")

    # Plot the zeros and poles
    ax.plot3D(np.real(z), np.imag(z), np.zeros_like(z), 'o', label="Zeros")
    ax.plot3D(np.real(p), np.imag(p), np.zeros_like(p), 'x', label="Poles")

    ax.set_xlabel("Real")
    ax.set_ylabel("Imaginary")
    ax.set_title("Pole Zero Plot")
    ax.legend()
    ax.view_init(35, 40)

    plt.grid()
    plt.show()


def PlotIIREQStepResponse(*filter_bands):
    """
    PLOT IIR EQ STEP RESPONSE: A function to plot the step response of an
    IIR filter, given a set of filter bands.

    Parameters:
    - filter_bands: An array of IIR filter coefficients.

    Returns:
    - None
    """
    # Setting the sampling n points for the plot to display
    n = 2048

    b_total = 1
    a_total = 1

    # Go through each filter band and get the coeffs
    for band in range(len(filter_bands)):
        fs = filter_bands[band].fs

        b, a = filter_bands[band].calculate_coefficients()
        impulse_response = np.zeros(n)
        impulse_response[0] = 1
        h = lfilter(b, a, impulse_response)  # getting the points to plot the step response using the coeffs

        # Plot the response
        plt.plot(h, label=filter_bands[band].filterName)
        # plt.hold(True)  # plotting all coeffs on the same graph

        # Convolve all coeffs for final response
        b_total = np.convolve(b_total, b)
        a_total = np.convolve(a_total, a)

    # Plot the average filter step response for all filter bands convolved
    impulse_response = np.zeros(n)
    impulse_response[0] = 1
    h = lfilter(b_total, a_total, impulse_response)
    plt.plot(h, color="red", linewidth=1, linestyle=":", label="All Filters")

    # plt.hold(False)  # stopping the plotting on the same graph

    plt.legend()
    plt.xlabel('Samples (n)')  # setting the label for the x axis
    plt.ylabel('Amplitude (V)')  # setting the label for the y axis
    plt.title("Step Response")
    plt.show()


def PlotIIREQPhaseResponse(*filter_bands):
    """
    PLOT IIR EQ PHASE RESPONSE: A function to plot the phase response of an
    IIR filter, given a set of filter bands.

    Parameters:
    - filter_bands: An array of IIR filter coefficients.

    Returns:
    - None
    """
    # Setting the sampling n points for the plot to display
    n = 2048

    b_total = 1
    a_total = 1

    # Go through each filter band and get the coeffs
    for band in range(len(filter_bands)):
        fs = filter_bands[band].fs

        b, a = filter_bands[band].calculate_coefficients()
        w, phi = freqz(b, a, worN=n, fs=fs)  # getting the points to plot the phase response using the coeffs
        phi = np.angle(phi)

        # Plot the response
        plt.semilogx(w, np.rad2deg(phi), label=filter_bands[band].filterName)
        # plt.hold(True)  # plotting all coeffs on the same graph

        # Convolve all coeffs for final response
        b_total = np.convolve(b_total, b)
        a_total = np.convolve(a_total, a)

    # Plot the average filter phase response for all filter bands convolved
    w, phi = freqz(b_total, a_total, worN=n, fs=fs)
    phi = np.angle(phi)

    plt.semilogx(w, np.rad2deg(phi), color="red", linewidth=1, linestyle=":", label="All Filters")

    plt.grid(True)  # turn grid on for the plot
    # plt.hold(False)  # stopping the plotting on the same graph

    plt.legend()

    # Setting configurations for the plot
    plt.ylim([-360, 360])  # setting the y limits to be -360deg to 360deg
    plt.xlim([20, 20000])  # setting the x limits to be 20Hz to 20kHz

    plt.xticks([20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000],
               ["20", "50", "100", "200", "500", "1k", "2k", "5k", "10k", "20k"])
    plt.yticks([-360, -315, -270, -225, -180, -135, -90, -45, 0, 45, 90, 135, 180, 225, 270, 315, 360],
               ["-360°", "-315°", "-270°", "-225°", "-180°", "-135°", "-90°", "-45°", "0", "45°", "90°", "135°",
                "180°", "225°", "270°", "315°", "360°"])

    plt.xlabel('Frequency (Hz)')  # setting the label for the x axis
    plt.ylabel('Phase Shift (deg)')  # setting the label for the y axis
    plt.title("Phase Response")
    plt.show()