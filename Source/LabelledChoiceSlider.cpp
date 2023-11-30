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
    // Creating the slider attatchment and linking the parameter to this attachment using the parameter ID
    _sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToUse, parameterID, *this);

    // Setting the text for the slider as the label
    // * Don't send notification means that a listener won't need to be be notified of any changes to this text as it will be static
    _label.setText(stateToUse.getParameter(parameterID)->getLabel(), juce::dontSendNotification);

    // Setting the sliders styles
    setSliderStyle(juce::Slider::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    setSliderSnapsToMousePosition(false);
    setColour(trackColourId, juce::Colour(0xffc5c6ca));

    // Displays the slider's label component (only when the parent is displayed as well)
    addAndMakeVisible(_label);
}

LabelledChoiceSlider::~LabelledChoiceSlider()
{
}

//void LabelledChoiceSlider::valueChanged()
//{
//}

int LabelledChoiceSlider::getChoiceValue()
{
    return _choices[static_cast<int>(getValue())];
}
