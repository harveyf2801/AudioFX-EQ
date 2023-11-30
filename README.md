# AudioFX - EQ

## Configure Project

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

## Refferences

[JUCE Docs](https://docs.juce.com/)

### EQ Audio Processing

[Audio EQ Cookbook](https://webaudio.github.io/Audio-EQ-Cookbook/audio-eq-cookbook.html)

[Lowpass Highpass Filter in JUCE](https://thewolfsound.com/lowpass-highpass-filter-plugin-with-juce/)

[Lock Free Queues (Pure C++ Implimentation)](https://jbseg.medium.com/lock-free-queues-e48de693654b)

[Boost Single-writer/Single-reader FIFO Queue](https://www.boost.org/doc/libs/1_53_0/doc/html/boost/lockfree/spsc_queue.html)

### GUI

[Spectrum Analyser JUCE Tutorial](https://docs.juce.com/master/tutorial_spectrum_analyser.html)

[Spectogram JUCE Tutorial](https://docs.juce.com/master/tutorial_simple_fft.html)

[Simple EQ Tutorial](https://www.youtube.com/watch?v=i_Iq4_Kd7Rc&ab_channel=freeCodeCamp.org)
