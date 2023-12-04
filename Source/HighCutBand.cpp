/*
  ==============================================================================

    HighCutBand.cpp
    Created: 4 Dec 2023 1:40:56pm
    Author:  Harvey

  ==============================================================================
*/

#include "HighCutBand.h"
#include <cmath>

//==============================================================================

HighCutBand::HighCutBand()
{
}

HighCutBand::~HighCutBand()
{
}

void HighCutBand::updateCoefficients(float frequency, float Q, float sampleRate)
{
    // Intermediate variables
    float w0 = 2 * juce::MathConstants<float>::pi * frequency / sampleRate;
    float alpha = std::sin(w0) / (2 * Q);

    // Calculate filter coefficients
    float b0 = (1 - std::cos(w0)) / 2;
    float b1 = 1 - std::cos(w0);
    float b2 = (1 - std::cos(w0)) / 2;
    float a0 = 1 + alpha;
    float a1 = -2 * std::cos(w0);
    float a2 = 1 - alpha;
    
    _b = {b0, b1, b2};
    _a = {a0, a1, a2};
    
    normaliseCoefficients();
}