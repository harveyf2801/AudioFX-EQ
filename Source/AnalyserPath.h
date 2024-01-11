/*
  ==============================================================================

    AnalyserPath.h
    Created: 15 Dec 2023 7:45:00am
    Author:  Harvey

    Reference:
    [SimpleEQ - Yashita Namdeo](https://github.com/yashitanamdeo/SimpleEQ/tree/main)

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "SingleChannelFifo.h"
#include "FFTDataGenerator.h"
#include "AnalyserPathGenerator.h"

struct AnalyserPath
{
    // Constructor that takes a SingleChannelFifo as a parameter
    AnalyserPath(SingleChannelFifo<EQAudioProcessor::BlockType>& scsf);

    // Destructor
    ~AnalyserPath();

    // Process method that generates the path based on FFT data
    void process(juce::Rectangle<float> fftBounds, double sampleRate);

    // Get the generated path
    juce::Path getPath();

private:
    // Pointer to the SingleChannelFifo for the left channel
    SingleChannelFifo<EQAudioProcessor::BlockType>* leftChannelFifo;

    // AudioBuffer to store mono audio data
    juce::AudioBuffer<float> monoBuffer;

    // FFTDataGenerator for the left channel
    FFTDataGenerator<std::vector<float>> leftChannelFFTDataGenerator;

    // AnalyserPathGenerator for producing the visual path
    AnalyserPathGenerator<juce::Path> pathProducer;

    // Path object for the left channel FFT data
    juce::Path leftChannelFFTPath;
};