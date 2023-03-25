/*
  ==============================================================================

    CutBandParameters.h
    Created: 24 Mar 2023 8:06:19pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include "LabelledSlider.h"
#include "LabelledChoiceSlider.h"

class CutBandParameters : public juce::Component
{
public:
    CutBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID);
    ~CutBandParameters() override;

    void resized() override;

private:

    LabelledSlider _freqSlider;
    std::unique_ptr<LabelledChoiceSlider> _slopeSlider;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CutBandParameters)
};