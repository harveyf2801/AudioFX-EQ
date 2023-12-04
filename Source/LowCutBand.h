/*
  ==============================================================================

    LowPass.h
    Created: 3 Dec 2023 1:49:57pm
    Author:  Harvey Fretwell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AbstractFilterBand.h"

//==============================================================================

class LowCutBand : public AbstractFilterBand
{
public:
    LowCutBand();
    ~LowCutBand();

    void updateCoefficients(float frequency, float Q, float sampleRate);

private:

    // Declaring all private methods and attributes

    //==============================================================================

    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowCutBand)
};