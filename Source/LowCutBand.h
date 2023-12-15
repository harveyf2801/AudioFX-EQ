/*
  ==============================================================================

    LowPass.h
    Created: 3 Dec 2023 1:49:57pm
    Author:  Harvey Fretwell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AbstractBand.h"

//==============================================================================

class LowCutBand : public AbstractBand
{
public:
    LowCutBand();
    ~LowCutBand();

    // Implementation of the abstract function
    void updateCoefficients(float frequency, float Q, float sampleRate);
};