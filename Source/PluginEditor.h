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

#include "CustomLookAndFeel.h"

#include "GraphBackground.h"
#include "CutBandParameters.h"
#include "PeakBandParameters.h"
#include "ShelfBandParameters.h"

//==============================================================================

// Creating an EQ Editor class which inherits from the JUCE Audio Processor Editor
class EQAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================
    
    // Constructor / Destructor methods
    EQAudioProcessorEditor (EQAudioProcessor&);
    ~EQAudioProcessorEditor() override;

    //==============================================================================
    
    // This method is used to draw graphics on the plugin
    void paint (juce::Graphics&) override;
    
    // This is called everytime the window is resized and used
    // to recalculate all component sizes and positioning
    void resized() override;

private:
    
    // Declaring all private methods and attributes
    
    //==============================================================================
    
    // Declaring a custom look and feel for the GUI
    CustomLookAndFeel _customLookAndFeel;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EQAudioProcessor& _audioProcessor;
    
    // Declaring the spectral analyser for the plugin
    GraphBackground _graphBackground;
    
    // Declaring the cut and peaking band parameter groups for the plugin
    CutBandParameters _lowCutParams;
    CutBandParameters _highCutParams;
    
    // Declaring the cut and peaking band parameter groups for the plugin
    ShelfBandParameters _lowShelfParams;
    ShelfBandParameters _highShelfParams;

    juce::OwnedArray<PeakBandParameters> _peakBands;
    
    //==============================================================================
    
    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQAudioProcessorEditor)
};
