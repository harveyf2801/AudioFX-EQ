/*
  ==============================================================================

    FIFO.h
    Created: 27 Apr 2023 3:46:29pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Fifo
{
    void prepare(int numChannels, int numSamples);

    bool push(const juce::AudioBuffer<float>& buffer);
    bool pull(juce::AudioBuffer<float>& buffer);

    int getNumAvailableForReading() const;

private:
    static constexpr int Capacity = 30;
    std::array<juce::AudioBuffer<float>, Capacity> buffers;
    juce::AbstractFifo fifo{ Capacity };
};