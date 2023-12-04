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
    LowCutBand(float frequency, float Q, float sampleRate);
    ~LowCutBand();

    void setFreq(float frequency);
    void setQ(float Q);
    void setParams(float frequency, float Q);
    void setSampleRate(float sampleRate);

    juce::dsp::IIR::Coefficients<float>::Ptr getCoefficients();

private:

    // Declaring all private methods and attributes
    
    float _frequency;
    float _Q;
    float _sampleRate;

    float _b0, _b1, _b2, _a0, _a1, _a2;

    void recalculateCoefficients();

    //==============================================================================

    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowCutBand)
};