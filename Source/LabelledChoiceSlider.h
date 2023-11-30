/*
  ==============================================================================

    LabelledChoiceSlider.h
    Created: 8 Jan 2023 3:26:16pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// Creating a Labeled Choice Slider class which inherits from the JUCE Slider
// [Currently only allows integer choices]
class LabelledChoiceSlider : public juce::Slider
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================
    
    // Constructor / Destructor methods
    LabelledChoiceSlider(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID, juce::Array<int> choices);
    ~LabelledChoiceSlider() override;
    
    //==============================================================================
    
    // Returns the current choice value selected
    int getChoiceValue();
//    virtual void valueChanged();

private:
    
    // Declaring all private methods and attributes
    
    //==============================================================================
    
    // Declaring the array of integer choices
    juce::Array<int> _choices;
    
    // Declaring the label attribute for the slider
    juce::Label _label;
    
    // Declaring the slider attatchment attribute which links the parameter to the slider widget
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> _sliderAttachment;

    //==============================================================================
    
    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabelledChoiceSlider)
};
