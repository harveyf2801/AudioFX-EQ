/*
  ==============================================================================

    TDF2Biquad.cpp
    Created: 3 Dec 2023 9:41:06pm
    Author:  Harvey

  ==============================================================================
*/

#include "TDF2Biquad.h"
#include <cmath>

//==============================================================================

// Constructor that initializes the TDF2Biquad with given B and A coefficients

TDF2Biquad::TDF2Biquad(juce::dsp::IIR::Coefficients<float>* coeffs)
    : coefficients(coeffs)
{
    // Calculating the filter order
    order = coefficients->getFilterOrder();
}

// Method to process a single input sample through the filter
float TDF2Biquad::processSample(float sample)
{
    // Getting the raw coefficient values
    auto* c = coefficients->getRawCoefficients();

    auto output = (c[0] * sample) + state[0];

    // Filter computation using TDF2 structure
    for (size_t j = 0; j < order - 1; ++j)
        state[j] = (c[j + 1] * sample) - (c[order + j + 1] * output) + state[j + 1];

    state[order - 1] = (c[order] * sample) - (c[order * 2] * output);

    return output;
}

// Method to reset the filter's internal state
void TDF2Biquad::reset()
{
    // Reset filter state variables
    for (size_t i = 0; i < order; ++i)
        state[i] = 0;
}