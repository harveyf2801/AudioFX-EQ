/*
  ==============================================================================

    PeakBand.cpp
    Created: 4 Dec 2023 1:41:09pm
    Author:  Harvey

  ==============================================================================
*/

#include "PeakBand.h"
#include <cmath>

//==============================================================================

PeakBand::PeakBand()
{
}

PeakBand::~PeakBand()
{
}

void PeakBand::updateCoefficients(float frequency, float Q, float gain, float sampleRate)
{
    // Intermediate variables
    float w0 = 2 * juce::MathConstants<float>::pi * frequency / sampleRate;
    float alpha = std::sin(w0) / (2 * Q);
    float A = std::pow(10, gain / 40);

    // Calculate filter coefficients
    float b0 = 1 + alpha * A;
    float b1 = -2 * std::cos(w0);
    float b2 = 1 - alpha * A;
    float a0 = 1 + alpha / A;
    float a1 = -2 * std::cos(w0);
    float a2 = 1 - alpha / A;

    coefficients = std::make_shared<juce::dsp::IIR::Coefficients<float>>(
        b0 / a0,
        b1 / a0,
        b2 / a0,
        a0 / a0,
        a1 / a0,
        a2 / a0);
}