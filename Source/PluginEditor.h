/*
  ==============================================================================

    PluginEditor.h
    Created: 5 Aug 2022 10:05:54pm
    Author:  Harvey Fretwell
    
    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "GraphBackground.h"
#include "CutBandParameters.h"
#include "PeakBandParameters.h"

//==============================================================================
/**
*/
class EQAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    EQAudioProcessorEditor (EQAudioProcessor&);
    ~EQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EQAudioProcessor& _audioProcessor;

    GraphBackground _graphBackground;

    CutBandParameters _lowCutParams;
    CutBandParameters _highCutParams;

    juce::ShapeButton bbb;

    juce::OwnedArray<PeakBandParameters> _peakBands;

    juce::Rectangle<int> bounds;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQAudioProcessorEditor)
};
