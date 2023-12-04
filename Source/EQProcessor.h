/*
  ==============================================================================

    EQProcessor.h
    Created: 14 Dec 2022 1:30:13am
    Author:  Harvey Fretwell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class EQProcessor
{
public:

    EQProcessor ();
    ~EQProcessor();

    void process (juce::AudioBuffer<float>& buffer);

    void updateFilter();

private:

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> _lowPassFilter;
};