/*
  ==============================================================================

    LowPass.cpp
    Created: 3 Dec 2023 1:49:57pm
    Author:  Harvey Fretwell

  ==============================================================================
*/

#include "LowCutBand.h"
#include <cmath>

//==============================================================================


LowCutBand::LowCutBand(float frequency, float Q, float sampleRate)
    : _frequency(frequency)
    , _Q(Q)
    , _sampleRate(sampleRate)
{
    recalculateCoefficients();
}

LowCutBand::~LowCutBand()
{
}

void LowCutBand::setFreq(float frequency){
    _frequency = frequency;
    recalculateCoefficients();
}

void LowCutBand::setQ(float Q){
    _Q = Q;
    recalculateCoefficients();
}

void LowCutBand::setParams(float frequency, float Q){
    _frequency = frequency;
    _Q = Q;
    recalculateCoefficients();
}

void LowCutBand::setSampleRate(float sampleRate) {
    _sampleRate = sampleRate;
    recalculateCoefficients();
}

void LowCutBand::recalculateCoefficients()
{
    // Intermediate variables
    float w0 = 2 * juce::MathConstants<float>::pi * _frequency / _sampleRate;
    float alpha = std::sin(w0) / (2 * _Q);

    // Calculate filter coefficients
    _b0 = (1 + std::cos(w0)) / 2;
    _b1 = -(1 + std::cos(w0));
    _b2 = (1 + std::cos(w0)) / 2;
    _a0 = 1 + alpha;
    _a1 = -2 * std::cos(w0);
    _a2 = 1 - alpha;
}

juce::dsp::IIR::Coefficients<float>::Ptr LowCutBand::getCoefficients()
{
    return *new juce::dsp::IIR::Coefficients<float>(_b0, _b1, _b2, _a0, _a1, _a2);
}