# AudioFX - EQ

This project implements an audio equalizer using JUCE (Jules' Utility Class Extensions) and C++. By default, it includes 3 peaking bands, 2 shelves, and 2 cut bands for EQ processing. The peaking bands are dynamically implemented, allowing for easy adjustment of the number of bands by specifying the desired amount in the top of PluginProcessor.cpp. An all-pass filter band has been included in the project but has not been fully implemented in the GUI. All filter coefficients are calculated manually and applied using a Transposed Direct Form II BiQuad Filter.

## Configure Project

> :warning: **Cmake hasn't been updated since the last big update, therefore the project can instead be run and built using the ProJucer application.**

Configure for Windows
```console
cmake -G Visual Studio 17 2022 -S . -B build
```

Configure for MacOS
```console
cmake -G Xcode -S . -B build '-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64'
```

## Building Project

Build for Windows
```console
cmake --build . -j 12
```

Build for MacOS
```console
cd build
cmake --build . -j 8
```

## References

- [JUCE Docs](https://docs.juce.com/)

### EQ Audio Processing

- [Audio EQ Cookbook](https://webaudio.github.io/Audio-EQ-Cookbook/audio-eq-cookbook.html)

- [Lowpass Highpass Filter in JUCE](https://thewolfsound.com/lowpass-highpass-filter-plugin-with-juce/)

- [Lock Free Queues (Pure C++ Implimentation)](https://jbseg.medium.com/lock-free-queues-e48de693654b)

- [Boost Single-writer/Single-reader FIFO Queue](https://www.boost.org/doc/libs/1_53_0/doc/html/boost/lockfree/spsc_queue.html)

### GUI

- [Spectrum Analyser JUCE Tutorial](https://docs.juce.com/master/tutorial_spectrum_analyser.html)

- [Spectogram JUCE Tutorial](https://docs.juce.com/master/tutorial_simple_fft.html)

- [Simple EQ Tutorial](https://www.youtube.com/watch?v=i_Iq4_Kd7Rc&ab_channel=freeCodeCamp.org)
