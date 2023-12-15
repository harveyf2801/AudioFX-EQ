/*
  ==============================================================================

    AbstractBand.h
    Created: 15 Dec 2023 2:55:43am
    Author:  Harvey

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================

class AbstractBand
{
public:
    AbstractBand();
    ~AbstractBand();

    // Abstract function to get coefficients
    juce::dsp::IIR::Coefficients<float>* getCoefficients() const;

    bool isBypassed();
    void setPower(bool power);

protected:
    // Coefficients object
    std::shared_ptr<juce::dsp::IIR::Coefficients<float>> coefficients;
    bool _power = 0;
};