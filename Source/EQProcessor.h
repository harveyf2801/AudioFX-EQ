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

    void setLowCutParams(float frequency, float Q);

    void prepare(const juce::dsp::ProcessSpec& spec);

    void process(const juce::dsp::ProcessContextReplacing<float>& context) noexcept;

    //void updateFilter();

    void reset() noexcept;

private:

    enum
    {
        lowCutIndex,
        highCutIndex
    };

    double _sampleRate = 0;

    using StereoFilter = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>;

    juce::dsp::ProcessorChain<StereoFilter> _processorChain;
};