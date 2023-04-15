/*
  ==============================================================================

    Graph.h
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/


#pragma once

#include "JuceHeader.h"

class Graph : public juce::Component
{
public:
    Graph (const std::vector<float> &freqs, const std::vector<float>& gains);
    ~Graph () override;

    float getXMap (float value, float xmin, float xmax);
    float getYMap(float value, float xmin, float xmax);

    void paint (juce::Graphics& g) override;
    void resized () override;

private:

    // colours
    const juce::Colour backgroundColour = juce::Colour (16, 21, 24);
    const juce::Colour freqLineColour = juce::Colour (49, 54, 57);
    const juce::Colour gainLineColour = juce::Colour (41, 47, 47);
    const juce::Colour gain0LineColour = juce::Colour (141, 149, 152);
    const juce::Colour labelColour = gain0LineColour;

    // fonts
    const int fontHeight = 10;

    // ===========================

    std::vector<float> _freqs;
    std::vector<float> _gains;

    float _minFreq;
    float _maxFreq;
    float _minGain;
    float _maxGain;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Graph)
};