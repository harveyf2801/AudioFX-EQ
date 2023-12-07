/*
  ==============================================================================

    AbstractFilterBand.cpp
    Created: 4 Dec 2023 1:43:16pm
    Author:  Harvey

  ==============================================================================
*/

#include "AbstractFilterBand.h"
#include <cmath>

//==============================================================================

AbstractFilterBand::AbstractFilterBand()
{
}

AbstractFilterBand::~AbstractFilterBand()
{
}

juce::dsp::IIR::Coefficients<float>::Ptr AbstractFilterBand::getCoefficients()
{
    return *new juce::dsp::IIR::Coefficients<float>(_b0 / _a0,
                                                    _b1 / _a0,
                                                    _b2 / _a0,
                                                    _a0 / _a0,
                                                    _a1 / _a0,
                                                    _a2 / _a0);
}