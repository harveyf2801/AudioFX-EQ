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

TDF2Biquad::TDF2Biquad(std::vector<float>& b, std::vector<float>& a)
    : _b(b)
    , _a(a)
{
    _s1, _s2 = 0, 0;
}

void TDF2Biquad::setCoefficients(std::vector<float>& newB, std::vector<float>& newA)
{

    // Make sure coeffs a and b are equal in size (padding with zeros)
    jassert(newA.size() == newB.size());
    
    // Ensure that a0 is not zero
    jassert(newA[0] != 0.0f);

    _b = newB;
    _a = newA;

    //_s1, _s2 = 0, 0;
}

float TDF2Biquad::processSample(float X)
{
    jassert(_b.size() == 3);
    jassert(_a.size() == 3);

    float Y = _b[0] * X + _s1;

    _s1 = _b[1] * X - _a[1] * Y + _s2 ;
    _s2 = _b[2] * X - _a[2] * Y;

    return Y;
}

void TDF2Biquad::reset()
{
    _s1, _s2 = 0, 0;
}