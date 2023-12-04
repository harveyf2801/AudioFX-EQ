/*
  ==============================================================================

    EQProcessor.cpp
    Created: 14 Dec 2022 1:30:13am
    Author:  Harvey Fretwell

  ==============================================================================
*/

#include "EQProcessor.h"


EQProcessor::EQProcessor ()
{

}
EQProcessor::~EQProcessor()
{

}

void EQProcessor::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block (buffer);
}

void EQProcessor::updateFilter()
{

}