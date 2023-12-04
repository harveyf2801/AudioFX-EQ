/*
  ==============================================================================

    EQProcessor.cpp
    Created: 14 Dec 2022 1:30:13am
    Author:  Harvey Fretwell

  ==============================================================================
*/

#include "EQProcessor.h"


EQProcessor::EQProcessor () :
    _lowPassFilter (juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.f, 0.1f))
{

}
EQProcessor::~EQProcessor()
{

}

void EQProcessor::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block (buffer);
    _lowPassFilter.process (juce::dsp::ProcessContextReplacing<float>(block));
}

void EQProcessor::updateFilter()
{

}