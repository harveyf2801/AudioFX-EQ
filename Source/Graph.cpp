/*
  ==============================================================================

    Graph.cpp
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/

#include "Graph.h"


Graph::Graph(const std::vector<float>& freqs, const std::vector<float>& gains)
    : _freqs(freqs)
    , _gains(gains)
    , _minFreq(*std::ranges::min_element(_freqs))
    , _maxFreq(*std::ranges::max_element(_freqs))
    , _minGain(*std::ranges::min_element(_gains))
    , _maxGain(*std::ranges::max_element(_gains))
{
}

Graph::~Graph()
{
}

float Graph::getXMap(float value, float xmin, float xmax)
{
    auto normX = juce::mapFromLog10(value, _minFreq, _maxFreq);
    auto logXfreq = xmin + xmax * normX;

    return logXfreq;
}

float Graph::getYMap(float value, float ymin, float ymax)
{
    return juce::jmap(value, _minGain, _maxGain, ymin, ymax);
}

void Graph::paint(juce::Graphics& g)
{
    g.setColour(backgroundColour);
    g.fillAll(backgroundColour);

    // bounds
    
    auto container = getLocalBounds().reduced(fontHeight * 2);
    auto left = container.getX();
    auto right = container.getRight();
    auto top = container.getY();
    auto bottom = container.getBottom();
    auto width = container.getWidth();

    auto maxTextStartX = getWidth() - 40;

    auto cg = juce::ColourGradient(freqLineColour, container.getCentreX(), container.getCentreY(),
        juce::Colours::transparentBlack, right, top, true);

    /* ============================================== */

    for (auto freq : _freqs)
    {
        auto x = getXMap(freq, (float) left, (float) width);

        g.setGradientFill(cg);
        g.drawVerticalLine(x, top, bottom);

        juce::String str = (freq > 999.f) ? juce::String(freq / 1000.f) + "k" : juce::String(freq);
        str << "Hz";

        auto textWidth = g.getCurrentFont().getStringWidth(str);

        juce::Rectangle<int> r;

        r.setSize(textWidth, fontHeight);
        r.setCentre(x, 0);
        r.setY(1);

        g.setColour(labelColour);
        g.drawFittedText(str, r, juce::Justification::centred, 1);
    }

    /* ============================================== */

    for (auto gain : _gains)
    {
        auto y = getYMap(gain, (float) bottom, (float) top);

        juce::String str = (gain > 0) ? "+" : "";
        str << gain << "dB";
        auto textWidth = g.getCurrentFont().getStringWidth(str);

        auto lineColour = (gain == 0.f) ? gain0LineColour : gainLineColour;

        g.setGradientFill(cg);
        g.drawHorizontalLine(y, left, right);

        g.setColour(gainLineColour);

        juce::Rectangle<int> r;
        r.setSize(textWidth, fontHeight);
        r.setX(getWidth() - textWidth);
        r.setCentre(r.getCentreX(), y);

        g.drawFittedText(str, r, juce::Justification::centredLeft, 1);

        //str.clear();
        //str << (gain - _maxGain) << "dB";

        //r.setX(1);
        //textWidth = g.getCurrentFont().getStringWidth(str);
        //r.setSize(textWidth, fontHeight);

        //g.drawFittedText(str, r, juce::Justification::centredLeft, 1);
    }
}

void Graph::resized()
{
    //graphBounds = getLocalBounds();
    //borderTopBounds = graphBounds.removeFromTop(fontHeight);
    //borderLeftBounds = graphBounds.removeFromLeft(20);
    //borderRightBounds = graphBounds.removeFromRight(20);
}