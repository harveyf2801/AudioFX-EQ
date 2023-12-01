/*
  =============================================================================
    ShelfBandParameters
    Created: 1 Dec 2023 5:32:39
    Author:  Harvey Fretwel
  ============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PeakBandParameters.h"

class ShelfBandParameters : public PeakBandParameters
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================
    
    // Constructor / Destructor methods
    ShelfBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID);
   ~ ShelfBandParameters() override;
private:

   
    // Declaring all private methods and attributes
 
    //==============================================================================
    
    //SHOULD ALWAYS BE AT THE END OF THE JUCE CLASd
   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShelfBandParameters)
};

