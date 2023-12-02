/*
  ==============================================================================

    CutBandParameters.h
    Created: 24 Mar 2023 8:06:19pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "LabelledSlider.h"
#include "LabelledChoiceSlider.h"

//==============================================================================

class CutBandParameters : public juce::Component
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================
    
    // Constructor / Destructor methods
    CutBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID);
    ~CutBandParameters() override;

    //==============================================================================
    
    // This is called everytime the component is resized and used
    // to recalculate all component sizes and positioning
    void resized() override;

private:
    
    // Declaring all private methods and attributes
    
    //==============================================================================
    
    // Declaring all cut band parameters to contain in this section
    LabelledSlider _freqSlider;
    LabelledChoiceSlider _slopeSlider;
    LabelledSlider _qSlider;

    //==============================================================================
    
    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CutBandParameters)
};
