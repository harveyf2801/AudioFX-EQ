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

void AbstractFilterBand::normaliseCoefficients()
{
    for(size_t i = 0; i < _b.size(); ++i)
    {
        _b[i] /= _a[0];
    }
    for(size_t i = 0; i < _a.size(); ++i)
    {
        _a[i] /= _a[0];
    }
}

std::vector<float> AbstractFilterBand::getBCoefficients()
{
    return _b;
}

std::vector<float> AbstractFilterBand::getACoefficients()
{
    return _a;
}
