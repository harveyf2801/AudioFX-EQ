/*
  ==============================================================================

    AbstractFilterBand.h
    Created: 4 Dec 2023 1:43:16pm
    Author:  Harvey

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================

class AbstractFilterBand
{
public:
    AbstractFilterBand();
    ~AbstractFilterBand();

    virtual void updateCoefficients(float frequency, float Q, float sampleRate){};
    
    std::vector<float>& getBCoefficients();
    std::vector<float>& getACoefficients();

protected:

    // Declaring all private methods and attributes
    std::vector<float> _b, _a;
    
    void normaliseCoefficients();
};