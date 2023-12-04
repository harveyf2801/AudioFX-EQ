/*
  ==============================================================================

    EQProcessor.h
    Created: 14 Dec 2022 1:30:13am
    Author:  Harvey Fretwell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LowCutBand.h"

//==============================================================================


class EQProcessor
{
public:

    // Declaring all public methods and attributes

    //==============================================================================

    // Constructor / Destructor methods
    EQProcessor ();
    ~EQProcessor();

    void process (juce::AudioBuffer<float>& buffer);

    void updateFilter();

private:
    LowCutBand _lowCutFilter;

    juce::dsp::ProcessorChain<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> _processorChain;
};