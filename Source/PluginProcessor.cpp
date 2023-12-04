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

// Initialising the peaking bands availible in our plugin
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

    // Pass in the constructor parameters for the audio processor value tree state.
    // Here the audio processor is passed in by reference, an undo manager is provided as a reference,
    // we provide an ID of "Parameters" and then dynamically create our parameter
    // layout by calling the custom initParameterLayout method.
     , apvts (*this, &undoManager, "Parameters", initParameterLayout())
     , lowCutBand(8000, 1, 44100)
     , filter(lowCutBand.getCoefficients())
{
}

EQAudioProcessor::~EQAudioProcessor()
{
}

static juce::NormalisableRange<float> createCenterSkewRange(float min, float max, float step, float skewCenter)
{
    auto range = juce::NormalisableRange<float>(min, max, step);
    range.setSkewForCentre(skewCenter);
    return range;
}

static juce::Array<int> log_space(int start, int end, int num)
{
    // Ensure valid input
    if (start <= 0 || end <= 0 || num < 2)
        /*
        Invalid input. Ensure start and end are positive and num is greater than 1.
        */
        jassertfalse;

    // Calculate the logarithmic step
    double log_step = std::pow(static_cast<double>(end) / start, 1.0 / (num - 1));

    // Generate the logarithmically spaced values and round to integers
    juce::Array<int> log_values;
    for (int i = 0; i < num; ++i)
    {
        log_values.add(static_cast<int>(std::round(start * std::pow(log_step, i))));
    }

    return log_values;
}

juce::AudioProcessorValueTreeState::ParameterLayout EQAudioProcessor::initParameterLayout()
{
    // Creating a parameter layout so that we can add parameters to the plugin
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    /*
            Using Logic Pro X EQ as a comparison:
     
            Peaking Filters
                Frequency:
                    Min: 20        Max: 20       Step: 0.4       SkewFactor: 0.25
                Gain:
                    Min: -24       Max: +24      Step: 0.1       SkewFactor: 1
                Q:
                    Min: 0.1       Max: 100      Step: 0.01       SkewFactor: 0.25
     
            Cut Filters
                Frequency:
                    Min: 20        Max: 20       Step: 0.4       SkewFactor: 0.25
                Slope:
                    Choices: 6, 12, 8, 24, 36, 48
                Q:
                    Min: 0.1       Max: 100      Step: 0.01       SkewFactor: 0.25
            
            Shelving Filters
                Frequency:
                    Min: 20        Max: 20       Step: 0.4       SkewFactor: 0.25
                Gain:
                    Min: -24       Max: +24      Step: 0.1       SkewFactor: 1
                Q:
                    Min: 0.1       Max: 2        Step: 0.01      SkewFactor: 0.25
     */

    // Defining the default frequency parameter value for each band, equally spaced logarithmically
    auto defaultFreqs = log_space(20, 20000, 4 + peakingBands);
    
    // Defining the names for the cut and shelving bands
    auto cutShelfNames = juce::Array<juce::String>("Low", "High");

    // Iterating through the two cut bands
    for (auto i = 0; i < 2; ++i)
    {
        // Defining the band name and ID for each cut band in the format "{cut type}-cut-{parameter type}"
        juce::String bandName = cutShelfNames[i] + " Cut ";
        juce::String bandId = bandName.replaceCharacter(' ', '-').toLowerCase();

        // * For each Audio Parameter, we usually provide an:
        //      - ID (to link parameters to functions)
        //      - Name (visible to users)
        //      - Range / min, max, step, skew
        //      - Default value
        // * Parameter ID provides the param ID and a version hint (for AU plugins)
        // * Normalisable Range provides a min, max, and interval value
        
        // Adding the frequency parameter for each cut band (in Hz)
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bandId + "freq", 1),
            bandName + "Frequency",
            createCenterSkewRange(20.f, 20000.f, 0.4f, 1000.0f),
            static_cast<float>(defaultFreqs.removeAndReturn(i * (defaultFreqs.size() - 1)))));

        // Adding the slope parameter for each cut band (this goes up in dB/Octave)
        layout.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID(bandId + "slope", 1),
            bandName + "Slope", juce::StringArray("6", "12", "18", "24", "36", "48"), 0));

        // Adding the q parameter for each peak (in q width)
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bandId + "q", 1),
            bandName + "Q",
            createCenterSkewRange(0.1f, 100.f, 0.01f, 1.0f),
            1.0f));
    }

    // Iterating through the two shelf bands
    for (auto i = 0; i < 2; ++i)
    {
        // Defining the band name and ID for each shelf band in the format "{shelf type}-shelf-{parameter type}"
        juce::String bandName = cutShelfNames[i] + " Shelf ";
        juce::String bandId = bandName.replaceCharacter(' ', '-').toLowerCase();

        // Adding the frequency parameter for each shelf (in Hz)
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bandId + "freq", 1),
            bandName + "Frequency",
            createCenterSkewRange(20.f, 20000.f, 0.4f, 1000.f),
            static_cast<float>(defaultFreqs.removeAndReturn(i * (defaultFreqs.size() - 1)))));

        // Adding the gain parameter for each shelf (in dB)
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bandId + "gain", 1),
            bandName + "Gain",
            juce::NormalisableRange<float>(-24.f, 24.f, 0.1f, 1.f),
            0.0f));

        // Adding the q parameter for each shelf (in q width)
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bandId + "q", 1),
            bandName + "Q",
            createCenterSkewRange(0.1f, 2.f, 0.01f, 1.0f),
            1.0f));
    }

    // Iterating through the amount of peaking bands we specified above
    for (auto i = 1; i <= peakingBands; ++i)
    {
        // Defining the band name and ID for each peaking band in the format "peak-{peak number}-{parameter type}"
        juce::String bandName = "Peak " + juce::String(i) + " ";
        juce::String bandId = bandName.replaceCharacter(' ', '-').toLowerCase();
        
        // Adding the frequency parameter for each peak (in Hz)
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bandId + "freq", 1),
            bandName + "Frequency",
            createCenterSkewRange(20.f, 20000.f, 0.4f, 1000.f),
            static_cast<float>(defaultFreqs[i - 1])));
        
        // Adding the gain parameter for each peak (in dB)
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bandId + "gain", 1),
            bandName + "Gain",
            juce::NormalisableRange<float>(-24.f, 24.f, 0.1f, 1.f),
            0.0f));
        
        // Adding the q parameter for each peak (in q width)
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bandId + "q", 1),
            bandName + "Q",
            createCenterSkewRange(0.1f, 100.f, 0.01f, 1.0f),
            1.0f));
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

void EQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    const juce::dsp::ProcessSpec spec{ sampleRate, samplesPerBlock, getNumOutputChannels() };

    lowCutBand.setParams(*apvts.getRawParameterValue("low-cut-freq"),
                         *apvts.getRawParameterValue("low-cut-q"));
    lowCutBand.setSampleRate(sampleRate);

    filter.prepare(spec);
    filter.reset();
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
    // Removes high precision floating point values close to zero that may be computationally heavy
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
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    auto* channelData = buffer.getWritePointer (channel);

    //    for (auto i = 0; i < buffer.getNumChannels(); ++i)
    //    {
    //        auto sample = channelData[i];
    //    }
    //}

    juce::dsp::AudioBlock<float> block(buffer);

    lowCutBand.setParams(*apvts.getRawParameterValue("low-cut-freq"),
                         *apvts.getRawParameterValue("low-cut-q"));

    *filter.state = *lowCutBand.getCoefficients();

    filter.process(juce::dsp::ProcessContextReplacing<float>(block));
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

void EQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // Store value state tree parameters as XML file ...
    auto stateTree = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(stateTree.createXml());
    copyXmlToBinary(*xml, destData);
}

void EQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    // Load in previously saved parameters from XML file ...
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr && xmlState->hasTagName(apvts.state.getType())) {
        apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

//==============================================================================

// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EQAudioProcessor();
}
