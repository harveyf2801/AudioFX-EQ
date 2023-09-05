/*
  ==============================================================================

    LabelledSlider.h
    Created: 12 Dec 2022 11:41:16pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class LabelledSlider : public juce::Slider
{
public:
    LabelledSlider (juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID);
    ~LabelledSlider() override;

private:

    juce::Label _label;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> _sliderAttachment;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabelledSlider)
};
