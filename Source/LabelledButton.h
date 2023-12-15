/*
  ==============================================================================

    LabelledButton.h
    Created: 15 Dec 2023 6:06:02am
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// Creating a Labeled Button class which inherits from the JUCE Button
class LabelledButton : public juce::TextButton
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================

    // Constructor / Destructor methods
    LabelledButton(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID);
    ~LabelledButton() override;

private:
    
    // Declaring all private methods and attributes
    
    //==============================================================================
    
    // Declaring the button attatchment attribute which links the parameter to the button widget
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> _buttonAttachment;

    //==============================================================================
    
    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabelledButton)
};
