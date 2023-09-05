/*
  ==============================================================================

    PluginProcessor.cpp
    Created: 5 Aug 2022 10:05:54pm
    Author:  Harvey Fretwell
    
    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

// Initialising the peaking bands availible
int EQAudioProcessor::peakingBands = 3;

EQAudioProcessor::EQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : juce::AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
     , apvts (*this, nullptr, "Parameters", initParameterLayout())
{
}

EQAudioProcessor::~EQAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout EQAudioProcessor::initParameterLayout()
{
    // Creating a parameter layout
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    for (auto i = 1; i <= peakingBands; ++i)
    {
        float defaultFreq = (20000 - 20) / ((float)peakingBands + 1);
        juce::String bandName = "Peak " + juce::String(i) + " ";
        juce::String bandId = bandName.replaceCharacter(' ', '-').toLowerCase();

        layout.add(std::make_unique<juce::AudioParameterFloat>(bandId + "freq",
            bandName + "Frequency",
            juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f),
            defaultFreq * i));

        layout.add(std::make_unique<juce::AudioParameterFloat>(bandId + "gain",
            bandName + "Gain",
            juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f),
            0.0f));

        layout.add(std::make_unique<juce::AudioParameterFloat>(bandId + "q",
            bandName + "Q",
            juce::NormalisableRange<float>(0.1f, 10.f, 0.5f, 1.f),
            1.0f));
    }

    for (juce::String i : { "Low", "High" })
    {
        juce::String bandName = i + " Cut ";
        juce::String bandId = bandName.replaceCharacter(' ', '-').toLowerCase();

        std::cout << "Band Name: " << bandName << std::endl;
        std::cout << "BandId: " << bandId << std::endl;

        layout.add(std::make_unique<juce::AudioParameterFloat>(bandId + "freq",
            bandName + "Frequency",
            juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f),
            20.f));

        layout.add(std::make_unique<juce::AudioParameterInt>(bandId + "slope",
            bandName + "Slope", 0, 3, 0));
    }

    return layout;
}

//==============================================================================
const juce::String EQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EQAudioProcessor::setCurrentProgram (int /*index*/)
{
}

const juce::String EQAudioProcessor::getProgramName (int /*index*/)
{
    return {};
}

void EQAudioProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
void EQAudioProcessor::prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void EQAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // auto* channelData = buffer.getWritePointer (channel);
        
        // ..do something to the data...
    }
}

//==============================================================================
bool EQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EQAudioProcessor::createEditor()
{
    return new EQAudioProcessorEditor (*this);
}

//==============================================================================
void EQAudioProcessor::getStateInformation (juce::MemoryBlock& /*destData*/)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EQAudioProcessor::setStateInformation (const void* /*data*/, int /*sizeInBytes*/)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EQAudioProcessor();
}
