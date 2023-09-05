/*
  ==============================================================================

    FFTProcessor.h
    Created: 27 Apr 2023 10:31:57am
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include <boost/thread/thread.hpp>
//#include <boost/lockfree/spsc_queue.hpp>
//
//#include <boost/atomic.hpp>

class FFTProcessor
{
public:

    FFTProcessor ();
    ~FFTProcessor();

    const enum FFTOrder
    {
        order2048 = 11,
        order4096 = 12,
        order8192 = 13
    };

    static const auto fftOrder = FFTOrder::order2048;
    static constexpr auto fftSize = 1 << fftOrder; // 2 ** n;
    static const auto scopeSize = 512;

    void process (juce::AudioBuffer<float>& /*buffer*/);

private:

    std::unique_ptr<juce::dsp::FFT> _FFT;
};