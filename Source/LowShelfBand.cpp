/*
  ==============================================================================

    LowShelfBand.cpp
    Created: 8 Dec 2023 12:39:17am
    Author:  Harvey

  ==============================================================================
*/

#include "LowShelfBand.h"
#include <cmath>

//==============================================================================

LowShelfBand::LowShelfBand()
{
}

LowShelfBand::~LowShelfBand()
{
}

void LowShelfBand::updateCoefficients(float frequency, float Q, float gain, float sampleRate)
{
    // Intermediate variables
    float w0 = 2 * juce::MathConstants<float>::pi * frequency / sampleRate;
    float alpha = std::sin(w0) / (2 * Q);
    float A = std::pow(10, gain / 40);

    // Calculate filter coefficients
    float b0 = A * ((A + 1) - (A - 1) * std::cos(w0) + 2 * std::sqrt(A) * alpha);
    float b1 = 2 * A * ((A - 1) - (A + 1) * std::cos(w0));
    float b2 = A * ((A + 1) - (A - 1) * std::cos(w0) - 2 * std::sqrt(A) * alpha);
    float a0 = (A + 1) + (A - 1) * std::cos(w0) + 2 * std::sqrt(A) * alpha;
    float a1 = -2 * ((A - 1) + (A + 1) * std::cos(w0));
    float a2 = (A + 1) + (A - 1) * std::cos(w0) - 2 * std::sqrt(A) * alpha;

    coefficients = std::make_shared<juce::dsp::IIR::Coefficients<float>>(
        b0 / a0,
        b1 / a0,
        b2 / a0,
        a0 / a0,
        a1 / a0,
        a2 / a0);
}