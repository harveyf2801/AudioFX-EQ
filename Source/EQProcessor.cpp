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

void EQProcessor::setLowCutParams(bool power, float frequency, float Q)
{
    // Set the parameters for the low-cut filter in the processor chain.
    // Updates the state of the low-cut filter with new coefficients based on frequency, Q, and sample rate.
    lowCutBand.setPower(power);
    _processorChain.setBypassed<lowCutIndex>(lowCutBand.isBypassed());

    if (power)
    {
        lowCutBand.updateCoefficients(frequency, Q, _sampleRate);
        *_processorChain.get<lowCutIndex>().state = *lowCutBand.getCoefficients();
    }
}

void EQProcessor::setLowShelfParams(bool power, float frequency, float Q, float gain)
{
    // Set the parameters for the low-shelf filter in the processor chain.
    // Updates the state of the low-shelf filter with new coefficients based on frequency, Q, gain, and sample rate.
    lowShelfBand.setPower(power);
    _processorChain.setBypassed<lowShelfIndex>(lowShelfBand.isBypassed());

    if (power)
    {
        lowShelfBand.updateCoefficients(frequency, Q, gain, _sampleRate);
        *_processorChain.get<lowShelfIndex>().state = *lowShelfBand.getCoefficients();
    }
}

void EQProcessor::setPeakParams(int index, bool power, float frequency, float Q, float gain)
{
    // Set the parameters for a peaking filter in the processor chain, based on the given index.
    // Updates the state of the specified peaking filter with new coefficients based on frequency, Q, gain, and sample rate.

    switch (index)
    {
    case 0:
        peakBand1.setPower(power);
        _processorChain.setBypassed<peak1Index>(peakBand1.isBypassed());
        if (power)
        {
            peakBand1.updateCoefficients(frequency, Q, gain, _sampleRate);
            *_processorChain.get<peak1Index>().state = *peakBand1.getCoefficients();
        }
        break;
    case 1:
        peakBand2.setPower(power);
        _processorChain.setBypassed<peak2Index>(peakBand2.isBypassed());
        if (power)
        {
            peakBand2.updateCoefficients(frequency, Q, gain, _sampleRate);
            *_processorChain.get<peak2Index>().state = *peakBand2.getCoefficients();
        }
        break;
    default:
        // index should be 0 1 or 2 for peaking bands, unless more bands are added
        peakBand3.setPower(power);
        _processorChain.setBypassed<peak3Index>(peakBand3.isBypassed());
        if (power)
        {
            peakBand3.updateCoefficients(frequency, Q, gain, _sampleRate);
            *_processorChain.get<peak3Index>().state = *peakBand3.getCoefficients();
        }
        break;
    }
}

void EQProcessor::setHighShelfParams(bool power, float frequency, float Q, float gain)
{
    // Set the parameters for the high-shelf filter in the processor chain.
    // Updates the state of the high-shelf filter with new coefficients based on frequency, Q, gain, and sample rate.
    highShelfBand.setPower(power);
    _processorChain.setBypassed<highShelfIndex>(highShelfBand.isBypassed());
    if (power)
    {
        highShelfBand.updateCoefficients(frequency, Q, gain, _sampleRate);
        *_processorChain.get<highShelfIndex>().state = *highShelfBand.getCoefficients();
    }
}

void EQProcessor::setHighCutParams(bool power, float frequency, float Q)
{
    // Set the parameters for the high-cut filter in the processor chain.
    // Updates the state of the high-cut filter with new coefficients based on frequency, Q, and sample rate.
    highCutBand.setPower(power);
    _processorChain.setBypassed<highCutIndex>(highCutBand.isBypassed());
    if (power)
    {
        highCutBand.updateCoefficients(frequency, Q, _sampleRate);
        *_processorChain.get<highCutIndex>().state = *highCutBand.getCoefficients();
    }
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