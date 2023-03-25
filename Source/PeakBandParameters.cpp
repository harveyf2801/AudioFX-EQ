/*
  ==============================================================================

    PeakBandParameters.cpp
    Created: 24 Mar 2023 8:07:00pm
    Author:  Harvey

  ==============================================================================
*/

#include "PeakBandParameters.h"

PeakBandParameters::PeakBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID)
    : _freqSlider(stateToUse, parameterID + "-freq")
    , _gainSlider(stateToUse, parameterID + "-gain")
    , _qSlider(stateToUse, parameterID + "-q")
{
    _freqSlider.setTextValueSuffix(" Hz");
    _gainSlider.setTextValueSuffix(" gain");

    addAndMakeVisible(_freqSlider);
    addAndMakeVisible(_gainSlider);
    addAndMakeVisible(_qSlider);

    //setSize(x, y)
}

PeakBandParameters::~PeakBandParameters()
{
}

void PeakBandParameters::resized()
{
    auto bounds = getLocalBounds();
    auto height = bounds.getHeight() / 3;

    _freqSlider.setBounds(bounds.removeFromTop(height));
    _gainSlider.setBounds(bounds.removeFromTop(height));
    _qSlider.setBounds(bounds.removeFromTop(height));
}