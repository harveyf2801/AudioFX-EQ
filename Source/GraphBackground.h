/*
  ==============================================================================

    GraphBackground
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/


#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class GraphBackground : public juce::Component,
                        public juce::AudioProcessorValueTreeState::Listener
{
public:
    
    // Declaring all public methods and attributes
    
    //==============================================================================
    
    // Constructor / Destructor methods
    GraphBackground (const juce::Array<float>& freqs, const juce::Array<float>& gains, EQAudioProcessor& p);
    ~GraphBackground () override;

    //==============================================================================
    
    // This updates the mapping of the X and Y lines
    void updateXMap(float xmin, float xmax);
    void updateYMap(float xmin, float xmax);

    // Updating the response curve of the graph
    void drawResponseCurve();

    // Updating the drawing of the graphs background image
    void drawBackground();
    
    // Paints the current component image
    void paint (juce::Graphics& g) override;
    
    // Called when the component is resized, then updates all of the lines on the graph
    void resized () override;

    void parameterChanged(const juce::String& parameterID, float newValue) override;
    
    // All colour IDs for the component
    enum ColourIds
    {
        backgroundColourId = 0x2000000,
        freqLineColourId = 0x2000001,
        gainLineColourId = 0x2000002,
        gain0LineColourId = 0x2000003,
        labelColourId = 0x2000004
    };
    
    float const fontHeight = 15;

private:
    
    // Declaring all private methods and attributes
    
    //==============================================================================
    
    // Declaring the array of frequency tick labels to be shown on the graph
    juce::Array<float> _freqs;
    juce::Array<float> _gains;
    
    // Declaring the array of frequency ticks lines to be shown on the graph in a log scale.
    // This is what gets remapped and updated on each resize call.
    juce::Array<float> _logFreqs;
    juce::Array<float> _logGains;
    
    // The minimum and maximum frequencys and gains to help with plotting
    float _minFreq;
    float _maxFreq;
    float _minGain;
    float _maxGain;

    // Declaring the background image to draw onto
    juce::Image background;
    
    // Declaring the colour gradient component to draw lines with
    juce::ColourGradient _colourGradient;

    juce::Path responseCurve;

    EQAudioProcessor& audioProcessor;

    juce::Rectangle<int> innerGraphContainer;

    //==============================================================================
    
    // SHOULD ALWAYS BE AT THE END OF THE JUCE CLASS
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphBackground)
};
