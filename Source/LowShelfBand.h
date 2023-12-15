/*
  ==============================================================================

    LowShelfBand.h
    Created: 8 Dec 2023 12:39:17am
    Author:  Harvey

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AbstractBand.h"

//==============================================================================

class LowShelfBand : public AbstractBand
{
public:
    LowShelfBand();
    ~LowShelfBand();

    // Implementation of the abstract function
    void updateCoefficients(float frequency, float Q, float gain, float sampleRate);

};