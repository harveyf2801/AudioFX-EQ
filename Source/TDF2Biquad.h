/*
  ==============================================================================

    TDF2Biquad.h
    Created: 3 Dec 2023 9:41:06pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class TDF2Biquad
{
public:
    // Constructor that takes B and A coefficients for the filter
    TDF2Biquad(juce::dsp::IIR::Coefficients<float>* coeffs);
    /*TDF2Biquad(const TDF2Biquad&) = default;
    TDF2Biquad(TDF2Biquad&&) = default;
    TDF2Biquad& operator= (const TDF2Biquad&) = default;
    TDF2Biquad& operator= (TDF2Biquad&&) = default;*/

    // Method to process a single input sample through the filter
    float processSample(float sample);

    // Method to reset the filter's internal state
    void reset();

    // B and A coefficients for the filter
    juce::dsp::IIR::Coefficients<float>* coefficients;

private:

    // Initial condition for filter delays
    float* state = nullptr;

    // The order of the filter being applied
    size_t order = 0;
};