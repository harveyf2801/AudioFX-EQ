/*
  ==============================================================================

    EQProcessor.h
    Created: 14 Dec 2022 1:30:13am
    Author:  Harvey Fretwell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LowCutBand.h"
#include "LowShelfBand.h"
#include "PeakBand.h"
#include "HighShelfBand.h"
#include "HighCutBand.h"

//==============================================================================

class EQProcessor
{
public:

    // Declaring all public methods and attributes

    //==============================================================================

    // Constructor / Destructor methods
    EQProcessor();
    ~EQProcessor();

    void setLowCutParams(bool power, float frequency, float Q);
    void setLowShelfParams(bool power, float frequency, float Q, float gain);
    void setPeakParams(int index, bool power, float frequency, float Q, float gain);
    void setHighShelfParams(bool power, float frequency, float Q, float gain);
    void setHighCutParams(bool power, float frequency, float Q);

    void prepare(const juce::dsp::ProcessSpec& spec);

    void process(const juce::dsp::ProcessContextReplacing<float>& context) noexcept;

    void reset() noexcept;

    // Declaring the eq band objects
    LowCutBand lowCutBand;
    LowShelfBand lowShelfBand;
    PeakBand peakBand1;
    PeakBand peakBand2;
    PeakBand peakBand3;
    HighShelfBand highShelfBand;
    HighCutBand highCutBand;

private:

    // Enumerated values for the eq band ID's
    enum _bandIndex
    {
        lowCutIndex,
        lowShelfIndex,
        highShelfIndex,
        highCutIndex,
        peak1Index,
        peak2Index,
        peak3Index
    };

    double _sampleRate = 44100; // setting sample rate at default 44100
                                // this gets set in the prepare method

    // Creating a processor duplicator to process multiple IIR filters at once
    using StereoIIRFilter = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>;

    // Adding these processors together in a processor chain
    juce::dsp::ProcessorChain<StereoIIRFilter, StereoIIRFilter,
                              StereoIIRFilter, StereoIIRFilter,
                              StereoIIRFilter, StereoIIRFilter,
                                               StereoIIRFilter> _processorChain;
};