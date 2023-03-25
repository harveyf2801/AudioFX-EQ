/*
  ==============================================================================

    LabelledChoiceSlider.h
    Created: 8 Jan 2023 3:26:16pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class LabelledChoiceSlider : public juce::Slider
{
public:
    LabelledChoiceSlider(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID, juce::Array<int> choices);
    ~LabelledChoiceSlider() override;

    int getChoiceValue();
    virtual void valueChanged();

private:

    juce::Array<int> _choices;
    juce::Label _label;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> _sliderAttachment;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabelledChoiceSlider)
};
