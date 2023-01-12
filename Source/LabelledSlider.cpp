/*
  ==============================================================================

    LabelledSlider.cpp
    Created: 12 Dec 2022 11:41:16pm
    Author:  Harvey

  ==============================================================================
*/

#include "LabelledSlider.h"

//==============================================================================

LabelledSlider::LabelledSlider (juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID)
{
    _sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToUse, parameterID, *this);

    _label.setText(stateToUse.getParameter(parameterID)->getLabel(), juce::dontSendNotification);

    setRange(-128, 0, 0);
    setSliderStyle(juce::Slider::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    setSliderSnapsToMousePosition(false);
    setColour(trackColourId, juce::Colour(0xffc5c6ca));

}

LabelledSlider::~LabelledSlider()
{
}