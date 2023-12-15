/*
  =============================================================================
    ShelfBandParameters.c
    Created: 1 Dec 2023 5:32:39
    Author:  Harvey Fretwel
  ============================================================================
*/

#include "ShelfBandParameters.h"

//==============================================================================

ShelfBandParameters::ShelfBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID, const juce::String bandName)
: PeakBandParameters(stateToUse, parameterID, bandName)
{
}

ShelfBandParameters::~ShelfBandParameters()
{
}

