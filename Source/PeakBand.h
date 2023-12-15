/*
  ==============================================================================

    PeakBand.h
    Created: 4 Dec 2023 1:41:09pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AbstractBand.h"

//==============================================================================

class PeakBand : public AbstractBand
{
public:
    PeakBand();
    ~PeakBand();

    // Implementation of the abstract function
    void updateCoefficients(float frequency, float Q, float gain, float sampleRate);

};