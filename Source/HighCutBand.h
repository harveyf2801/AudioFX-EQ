/*
  ==============================================================================

    HighCutBand.h
    Created: 4 Dec 2023 1:40:56pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AbstractBand.h"

//==============================================================================

class HighCutBand : public AbstractBand
{
public:
    HighCutBand();
    ~HighCutBand();

    // Implementation of the abstract function
    void updateCoefficients(float frequency, float Q, float sampleRate);

};