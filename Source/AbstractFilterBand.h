/*
  ==============================================================================

    AbstractFilterBand.h
    Created: 4 Dec 2023 1:43:16pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================

class AbstractFilterBand
{
public:
    AbstractFilterBand();
    ~AbstractFilterBand();

    virtual void updateCoefficients(float frequency, float Q, float sampleRate){};
    
    juce::dsp::IIR::Coefficients<float>::Ptr getCoefficients();

protected:

    // Declaring all private methods and attributes
    float _b0, _b1, _b2, _a0, _a1, _a2;
};