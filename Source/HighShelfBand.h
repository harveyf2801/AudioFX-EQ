/*
  ==============================================================================

    HighShelfBand.h
    Created: 8 Dec 2023 12:39:27am
    Author:  Harvey

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AbstractBand.h"

//==============================================================================

class HighShelfBand : public AbstractBand
{
public:
    HighShelfBand();
    ~HighShelfBand();

    // Implementation of the abstract function
    void updateCoefficients(float frequency, float Q, float gain, float sampleRate);

};