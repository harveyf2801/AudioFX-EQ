/*
  ==============================================================================

    PluginProcessor.h
    Created: 5 Aug 2022 10:05:54pm
    Author:  Harvey Fretwell
    
    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LowCutBand.h"
#include "TDF2Biquad.h"

//==============================================================================

// Creating an EQ Audio Processor class which inherits from the JUCE Audio Processor
class EQAudioProcessor : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================
    
    // Constructor / Destructor methods
    EQAudioProcessor();
    ~EQAudioProcessor() override;

    //==============================================================================
    
    // Used to prepare any audio before playback
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    
    // Used to perform any processing after playback is stopped
    void releaseResources() override;
    
    // Used to configure any channel configurations for the plugin
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
    
    // The main processing method for the plugins audio
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    
    // Creates the editor for the plugin
    juce::AudioProcessorEditor* createEditor() override;
    
    // Returns True or False if an editor is provided.
    // If not provided, either use JUCE built in GenericAudioProcessorEditor in createEditor method.
    bool hasEditor() const override;

    //==============================================================================
    
    // Provides the name of the audio plugin
    const juce::String getName() const override;
    
    // MIDI methods
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    
    // Allows a tail of audio after pausing the playback.
    // Used for example with reverbs or delays.
    double getTailLengthSeconds() const override;

    //==============================================================================
    
    // To provide default presets for the plugin
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    
    // Allows saving and loading of user presets for the plugin
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    
    // Declaring the peaking bands attribute.
    // This attribute provides the number of peaking bands that will
    // be dynamically created in the plugin.
    static int peakingBands;
    
    // Declaring an undo manager so that parameters can be undone and redone by the user
    juce::UndoManager undoManager;

    // Declaring a custom function which provides a parameter layout, used
    // when constructing the audio processor value tree state.
    static juce::AudioProcessorValueTreeState::ParameterLayout initParameterLayout();
    
    // Declaring the Audio Processor Value Tree State
    juce::AudioProcessorValueTreeState apvts;

private:
    
    // Declaring all private methods and attributes
    
    //==============================================================================
    
    // Declaring the EQ processor which will be used to perform
    // the audio processing of the EQ plugin.
    LowCutBand lowCutBand;
    juce::Array<TDF2Biquad> filterChain;

    //==============================================================================
    
    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQAudioProcessor)
};
