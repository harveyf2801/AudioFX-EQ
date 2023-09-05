/*
  ==============================================================================

    PeakBandParameters.h
    Created: 24 Mar 2023 8:07:00pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "GUI/components/LabelledSlider.h"
#include "GUI/components/LabelledChoiceSlider.h"

class PeakBandParameters : public juce::Component
{
public:
    PeakBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID);
    ~PeakBandParameters() override;

    void resized() override;

private:

    LabelledSlider _freqSlider;
    LabelledSlider _gainSlider;
    LabelledSlider _qSlider;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakBandParameters)
};