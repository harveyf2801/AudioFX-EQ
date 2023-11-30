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

LabelledSlider::~LabelledSlider()
{
}
