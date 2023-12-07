/*
  ==============================================================================

    LowPass.h
    Created: 3 Dec 2023 1:49:57pm
    Author:  Harvey Fretwell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class LowCutBand
{
public:
    LowCutBand();
    ~LowCutBand();

    juce::dsp::IIR::Coefficients<float>::Ptr getCoefficients(float frequency, float Q, float sampleRate);

private:

    // Declaring all private methods and attributes

    //==============================================================================

};