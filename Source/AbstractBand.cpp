/*
  ==============================================================================

    AbstractBand.cpp
    Created: 15 Dec 2023 2:55:43am
    Author:  Harvey

  ==============================================================================
*/

#include "AbstractBand.h"

AbstractBand::AbstractBand()
{

}

AbstractBand::~AbstractBand()
{

}

juce::dsp::IIR::Coefficients<float>* AbstractBand::getCoefficients() const
{
    return coefficients.get();
}

bool AbstractBand::isBypassed()
{
    return !_power;
}

void AbstractBand::setPower(bool power)
{
    _power = power;
}