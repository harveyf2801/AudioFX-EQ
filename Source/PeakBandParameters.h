/*
  ==============================================================================

    PeakBandParameters.h
    Created: 24 Mar 2023 8:07:00pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "LabelledSlider.h"
#include "LabelledChoiceSlider.h"

class PeakBandParameters : public juce::Component
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================
    
    // Constructor / Destructor methods
    PeakBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID);
    ~PeakBandParameters() override;
    
    //==============================================================================
    
    // This is called everytime the component is resized and used
    // to recalculate all component sizes and positioning
    void resized() override;

protected:
    
    // Declaring all protected methods and attributes
    
    //==============================================================================
    
    // Declaring all peaking band parameters to contain in this section
    LabelledSlider _freqSlider;
    LabelledSlider _gainSlider;
    LabelledSlider _qSlider;

private:
    
    // Declaring all private methods and attributes

    //==============================================================================
    
    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakBandParameters)
};
