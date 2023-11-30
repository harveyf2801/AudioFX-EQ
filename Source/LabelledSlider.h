/*
  ==============================================================================

    LabelledSlider.h
    Created: 12 Dec 2022 11:41:16pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// Creating a Labeled Slider class which inherits from the JUCE Slider
class LabelledSlider : public juce::Slider
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================

    // Constructor / Destructor methods
    LabelledSlider (juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID);
    ~LabelledSlider() override;

private:
    
    // Declaring all private methods and attributes
    
    //==============================================================================
    
    // Declaring the label attribute for the slider
    juce::Label _label;
    
    // Declaring the slider attatchment attribute which links the parameter to the slider widget
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> _sliderAttachment;

    //==============================================================================
    
    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabelledSlider)
};
