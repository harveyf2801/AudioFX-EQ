/*
  ==============================================================================

    HighCutBand.h
    Created: 4 Dec 2023 1:40:56pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AbstractFilterBand.h"

//==============================================================================

class HighCutBand : public AbstractFilterBand
{
public:
    HighCutBand();
    ~HighCutBand();

    void updateCoefficients(float frequency, float Q, float sampleRate);

private:

    // Declaring all private methods and attributes

    //==============================================================================

};