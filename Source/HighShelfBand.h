/*
  ==============================================================================

    HighShelfBand.h
    Created: 8 Dec 2023 12:39:27am
    Author:  Harvey

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================

class HighShelfBand
{
public:
    HighShelfBand();
    ~HighShelfBand();

    juce::dsp::IIR::Coefficients<float>::Ptr getCoefficients(float frequency, float Q, float gain, float sampleRate);

private:

    // Declaring all private methods and attributes

    //==============================================================================

};