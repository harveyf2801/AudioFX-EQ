/*
  ==============================================================================

    LabelledChoiceSlider.cpp
    Created: 8 Jan 2023 3:26:16pm
    Author:  Harvey

  ==============================================================================
*/

#include "LabelledChoiceSlider.h"


//==============================================================================

LabelledChoiceSlider::LabelledChoiceSlider(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID, juce::Array<int> choices)
    : _choices (choices)
{
    _sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToUse, parameterID, *this);

    _label.setText(stateToUse.getParameter(parameterID)->getLabel(), juce::dontSendNotification);

    setSliderStyle(juce::Slider::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    setSliderSnapsToMousePosition(false);
    setColour(trackColourId, juce::Colour(0xffc5c6ca));

    addAndMakeVisible(_label);
}

LabelledChoiceSlider::~LabelledChoiceSlider()
{
}

void LabelledChoiceSlider::valueChanged()
{
}

int LabelledChoiceSlider::getChoiceValue()
{
    return _choices[static_cast<int>(getValue())];
}