/*
  ==============================================================================

    EQProcessor.cpp
    Created: 14 Dec 2022 1:30:13am
    Author:  Harvey Fretwell

  ==============================================================================
*/

#include "EQProcessor.h"

EQProcessor::EQProcessor()
{
}

EQProcessor::~EQProcessor()
{

}

void EQProcessor::setLowCutParams(float frequency, float Q)
{
    _processorChain.get<lowCutIndex>().state = juce::dsp::IIR::Coefficients<float>::makeHighPass(_sampleRate, frequency, Q);
}

void EQProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    _sampleRate = spec.sampleRate;
    _processorChain.prepare(spec);
}

void EQProcessor::process(const juce::dsp::ProcessContextReplacing<float>& context) noexcept
{
    _processorChain.process(context);
}

//template <typename SampleType>
//void EQProcessor<SampleType>::updateFilter()
//{
//
//}

void EQProcessor::reset() noexcept
{
    _processorChain.reset();
}