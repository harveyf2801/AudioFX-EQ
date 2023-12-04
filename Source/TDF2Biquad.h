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
    TDF2Biquad(std::vector<float> newB, std::vector<float> newA);

    void setCoefficients(std::vector<float> newB, std::vector<float> newA);

    float processSample(float X);

private:

    // Declaring all private methods and attributes
    
    // B and A coefficients for the filter
    std::vector<float> _b, _a;

    int _order;
    
    // Initial condition for filter delays
    float _s1, _s2;

    //==============================================================================

    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TDF2Biquad)
};