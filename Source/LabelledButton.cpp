/*
  ==============================================================================

    LabelledButton.cpp
    Created: 15 Dec 2023 6:06:02am
    Author:  Harvey

  ==============================================================================
*/

#include "LabelledButton.h"

//==============================================================================

LabelledButton::LabelledButton(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID)
{
    // Creating the button attatchment and linking the parameter to this attachment using the parameter ID
    _buttonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(stateToUse, parameterID, *this);
    
    // Setting the text for the button as the label
    setButtonText(stateToUse.getParameter(parameterID)->getLabel());
    
    // Setting the buttons styles
    setClickingTogglesState(true);
}

LabelledButton::~LabelledButton()
{
}