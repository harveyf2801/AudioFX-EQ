/*
  ==============================================================================

    SpectralAnalyser.h
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/


#pragma once

#include "JuceHeader.h"

class SpectralAnalyser : public juce::Component
{
public:
    SpectralAnalyser (const juce::Array<float>& freqs, const juce::Array<float>& gains);
    ~SpectralAnalyser () override;

    void updateXMap(float xmin, float xmax);
    void updateYMap(float xmin, float xmax);

    void drawBackground();

    void paint (juce::Graphics& g) override;
    void resized () override;

private:

    // colours
    const juce::Colour backgroundColourId = juce::Colour (16, 21, 24);
    const juce::Colour freqLineColourId = juce::Colour (49, 54, 57);
    const juce::Colour gainLineColourId = juce::Colour (41, 47, 47);
    const juce::Colour gain0LineColourId = juce::Colour (141, 149, 152);
    const juce::Colour labelColourId = gain0LineColourId;

    // fonts
    const int fontHeight = 10;

    // ===========================

    juce::Array<float> _freqs;
    juce::Array<float> _gains;

    juce::Array<float> _logFreqs;
    juce::Array<float> _logGains;

    float _minFreq;
    float _maxFreq;
    float _minGain;
    float _maxGain;

    juce::Image background;
    juce::ColourGradient _colourGradient;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectralAnalyser)
};
