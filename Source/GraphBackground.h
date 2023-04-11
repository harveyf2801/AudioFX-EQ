/*
  ==============================================================================

    GraphBackground.h
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/


#pragma once

#include "JuceHeader.h"

class GraphBackground : public juce::Component
{
public:
    GraphBackground(const std::vector<float> &freqs, const std::vector<float>& gains);
    ~GraphBackground() override;

    std::vector<float> getLogXfreqs(int xmin, int xmax);

    void drawFreqLabels(juce::Graphics& g);
    void drawLeftGainLabels(juce::Graphics& g);
    void drawRightGainLabels(juce::Graphics& g);
    void drawGraph(juce::Graphics& g);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    // colours
    const juce::Colour backgroundColour = juce::Colour(16, 21, 24);
    const juce::Colour freqLineColour = juce::Colour(49, 54, 57);
    const juce::Colour gainLineColour = juce::Colour(41, 47, 47);
    const juce::Colour gain0LineColour = juce::Colour(141, 149, 152);
    const juce::Colour labelColour = gain0LineColour;

    // fonts
    const int fontHeight = 10;

    // ===========================

    std::vector<float> _freqs;
    std::vector<float> _gains;

    float _minGain;
    float _maxGain;

    juce::OwnedArray<juce::Label> _freqLabels;
    juce::OwnedArray<juce::Label> _leftGainLabels;
    juce::OwnedArray<juce::Label> _rightGainLabels;

    juce::Rectangle<int> graphBounds;
    juce::Rectangle<int> borderTopBounds;
    juce::Rectangle<int> borderLeftBounds;
    juce::Rectangle<int> borderRightBounds;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphBackground)
};