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
    *_processorChain.get<lowCutIndex>().state = *_lowCutBand.getCoefficients(frequency, Q, _sampleRate);
}

void EQProcessor::setLowShelfParams(float frequency, float Q, float gain)
{
    *_processorChain.get<lowShelfIndex>().state = *_lowShelfBand.getCoefficients(frequency, Q, gain, _sampleRate);
}

void EQProcessor::setPeakParams(int index, float frequency, float Q, float gain)
{
    switch (index)
    {
    case 0:
        *_processorChain.get<peak1Index>().state = *_peakBand.getCoefficients(frequency, Q, gain, _sampleRate);
    case 1:
        *_processorChain.get<peak2Index>().state = *_peakBand.getCoefficients(frequency, Q, gain, _sampleRate);
    case 2:
        *_processorChain.get<peak3Index>().state = *_peakBand.getCoefficients(frequency, Q, gain, _sampleRate);
    default:
        break;
    }
}

void EQProcessor::setHighShelfParams(float frequency, float Q, float gain)
{
    *_processorChain.get<highShelfIndex>().state = *_highShelfBand.getCoefficients(frequency, Q, gain, _sampleRate);
}

void EQProcessor::setHighCutParams(float frequency, float Q)
{
    *_processorChain.get<highCutIndex>().state = *_highCutBand.getCoefficients(frequency, Q, _sampleRate);
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