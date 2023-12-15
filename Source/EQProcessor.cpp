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
    // Constructor: Initializes an instance of EQProcessor.
}

EQProcessor::~EQProcessor()
{
    // Destructor: Cleans up resources when an instance of EQProcessor is destroyed.
}

void EQProcessor::setLowCutParams(float frequency, float Q)
{
    // Set the parameters for the low-cut filter in the processor chain.
    // Updates the state of the low-cut filter with new coefficients based on frequency, Q, and sample rate.
    *_processorChain.get<lowCutIndex>().state = *_lowCutBand.getCoefficients(frequency, Q, _sampleRate);
}

void EQProcessor::setLowShelfParams(float frequency, float Q, float gain)
{
    // Set the parameters for the low-shelf filter in the processor chain.
    // Updates the state of the low-shelf filter with new coefficients based on frequency, Q, gain, and sample rate.
    *_processorChain.get<lowShelfIndex>().state = *_lowShelfBand.getCoefficients(frequency, Q, gain, _sampleRate);
}

void EQProcessor::setPeakParams(int index, float frequency, float Q, float gain)
{
    // Set the parameters for a peaking filter in the processor chain, based on the given index.
    // Updates the state of the specified peaking filter with new coefficients based on frequency, Q, gain, and sample rate.
    switch (index)
    {
    case 0:
        *_processorChain.get<peak1Index>().state = *_peakBand.getCoefficients(frequency, Q, gain, _sampleRate);
        break;
    case 1:
        *_processorChain.get<peak2Index>().state = *_peakBand.getCoefficients(frequency, Q, gain, _sampleRate);
        break;
    default:
        // index should be 0 1 or 2 for peaking bands, unless more bands are added
        *_processorChain.get<peak3Index>().state = *_peakBand.getCoefficients(frequency, Q, gain, _sampleRate);
        break;
    }
}

void EQProcessor::setHighShelfParams(float frequency, float Q, float gain)
{
    // Set the parameters for the high-shelf filter in the processor chain.
    // Updates the state of the high-shelf filter with new coefficients based on frequency, Q, gain, and sample rate.
    *_processorChain.get<highShelfIndex>().state = *_highShelfBand.getCoefficients(frequency, Q, gain, _sampleRate);
}

void EQProcessor::setHighCutParams(float frequency, float Q)
{
    // Set the parameters for the high-cut filter in the processor chain.
    // Updates the state of the high-cut filter with new coefficients based on frequency, Q, and sample rate.
    *_processorChain.get<highCutIndex>().state = *_highCutBand.getCoefficients(frequency, Q, _sampleRate);
}

void EQProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    // Prepare the EQ processor for processing audio with the given processing specifications.
    // Sets the sample rate and prepares the internal processor chain.
    _sampleRate = spec.sampleRate;
    _processorChain.prepare(spec);
}

void EQProcessor::process(const juce::dsp::ProcessContextReplacing<float>& context) noexcept
{
    // Process audio through the EQ processor.
    // Applies the configured filter chain to the audio in the given context.
    _processorChain.process(context);
}

void EQProcessor::reset() noexcept
{
    // Reset the internal state of the EQ processor.
    // Clears any accumulated state in the processor chain.
    _processorChain.reset();
}