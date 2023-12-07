/*
  ==============================================================================

    PeakBand.h
    Created: 4 Dec 2023 1:41:09pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class PeakBand
{
public:
    PeakBand();
    ~PeakBand();

    juce::dsp::IIR::Coefficients<float>::Ptr getCoefficients(float frequency, float Q, float gain, float sampleRate);

private:

    // Declaring all private methods and attributes

    //==============================================================================

};