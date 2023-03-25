/*
  ==============================================================================

    CutBandParameters.cpp
    Created: 24 Mar 2023 8:06:19pm
    Author:  Harvey

  ==============================================================================
*/

#include "CutBandParameters.h"


CutBandParameters::CutBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID)
    : _freqSlider (stateToUse, parameterID + "-freq")
{
    juce::Array<int> slopeArray;
    for (auto i = 0; i < 4; ++i)
    {
        int value = (12 + i * 12);
        slopeArray.add(value);
    }

    _slopeSlider = std::make_unique <LabelledChoiceSlider>(stateToUse, parameterID + "-slope", slopeArray);

    _freqSlider.setTextValueSuffix(" Hz");
    _slopeSlider->setTextValueSuffix(" dB/Oct");

    addAndMakeVisible(_freqSlider);
    addAndMakeVisible(*_slopeSlider);

    //setSize(x, y)
}

CutBandParameters::~CutBandParameters()
{
}

void CutBandParameters::resized()
{
    auto bounds = getLocalBounds();
    auto height = bounds.getHeight() / 2;

    _freqSlider.setBounds(bounds.removeFromTop(height));
    _slopeSlider->setBounds(bounds.removeFromTop(height));
}